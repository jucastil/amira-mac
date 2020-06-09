/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup mclib mclib
/// @{
#ifndef MC_ODE_TEMPLATE_H
#define MC_ODE_TEMPLATE_H

#include "McWinDLLApi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "McMath.h"

/// Solver for ordinary differential equations (Runge-Kutta).
template<class VecType>
class McODE {

  public:
    enum ErrorCode {
        ODE_OK = 0,
        ODE_DOMAINERROR = 1,
        ODE_ZEROVELOCITY = 2,
        ODE_HMINREACHED = 3,
        ODE_FALLBACK = 4,
        ODE_UNKNOWNMETHOD = 5
    };

    /// Denotes different Runge-Kutta methods (RK21, RK32, RK43, RK54, RKCK).
    enum Method {
        ///
        RK21=0,
        ///
        RK32,
        ///
        RK43,
        ///
        RK54,
        ///
        RKCK
    };

    /// Constructor.
    McODE();

    /** @name Set methods. */
    //@{

    /** Set Runge-Kutta method to be used (default is RK43). For very
        rough vector fields RK32 should be used, while for very smooth
        fields RK54 or RKCK might be preferable. */
    void setMethod(Method method);

    /** If this is on the right hand side will be automatically normalized
        to unit length. Therefore the resulting integral curve will be
        parameterized in arc-length. This is the default behavior. */
    void setNormalization(int onOff);

    /** Set the minimum and maximum allowed step sizes. These values
        depend on the scale of the problem and therefore should always be
        set by the user. The defaults are 0.1 and 10, respectively. */
    void setHMinMax(float hMin, float hMax);

    /** Set the error tolerance. Since this class is designed to integrate
        spatial curves the tolerance is interpreted as an absolute error.
        Like hMin and hMax the desired tolerance depends on the scale of the
        problem. The default is 0.02, i.e., 1/5th of hMin. */
    void setTolerance(float tolerance);

    /** Set the sampling distance to be used for equi-distant sampling via
        @c next(). This value doesn't affect the integrator itself but
        merely the evaluation of the associated interpolation polynomial.
        The default value is 1. */
    void setHSampling(float hSampling);

    /** Set orientation multiplier. The right hand side is automatically
        multiplied by the given value. Therefore, if integral curves are
        to be computed in backward direction a value -1 should be used.
        The default is 1. */
    void setOrientation(float orientation);

    /** Set the right hand side of the ODE, i.e., the vector field. An
        arbitrary pointer can be specified in @c userData. This pointer
        will be passed to the evaluation routine in its third argument.
        The method should return 0 on success. Otherwise, a domain error
        is assumed. */
    void setRightHandSide(int (*f)(const VecType& r, VecType& f, void*),
        void* userData=0);


    /** configure if hMin should be checked after a successful step.
    defaults to 0 (no check)
    */
    void setCheckHMin(int setTo);

    //@}

    /** @name Get methods. */
    //@{

    /// Returns the current internal step size of the Runge-Kutta method.
    float getCurrentStepSize() const { return h; }

    /// Returns the current error state (0 == ok).
    ErrorCode getErrorState() const { return error; }

    /// Returns the current sampling position.
    const VecType& getPosition() const { return d0; }

    /// Returns interpolated tangent vector at current sampling position.
    const VecType& getTangent() const { return df0; }

    /// Returns interpolated curvature vector at current sampling position.
    const VecType& getCurvature() const { return dff0; }

    /// Returns the current position of the Runge-Kutta method.
    const VecType& getPositionRK() const { return r; }

    /// Returns tangent vector at current Runge-Kutta position.
    const VecType& getTangentRK() const { return f; }

    /** returns current settings: is hMin checked after a successful step?
    */
    int getCheckHMin() { return checkHMin; }
    //@}

    /** @name Compute methods. */
    //@{

    /** Initializes the integrator. The parameter @c hTry determines the
        initial step size for the Runge-Kutta integrator. If this value
        is negative, an estimate for the step size will be computed
        automatically. */
    void init(const VecType& r, float hTry=-1);

    ErrorCode next();

    /** Returns the next sample position on the field line. The distance
        between subsequent samples will be constant. The sampling distance
        can be controlled using @c setHSampling(). On success, 0 is
        returned. Otherwise, an error code is returned (ODE_DOMAINERROR,
        ODE_ZEROVELOCITY, ODE_HMINREACHED). If the flag @c cont is true,
        in case of an error the curve will be continued artificially by
        means of an interpolation polynomial. */
    ErrorCode next(VecType& r_next, int cont=0);

    /** This method is similar to the above @c next() method. However, in
        addition to the position @c r also the interpolated tangent vector
        at the current sampling position is returned. */
    ErrorCode next(VecType& r_next, VecType& f_next, int cont=0);

    /** This method is similar to the above @c next() method. However, it
        also returns the interpolated curvature vector at the current
        sampling position. */
    ErrorCode next(VecType& r_next, VecType& f_next, VecType& ff_next, int cont=0);

    /** This method performs a Runge-Kutta step. If necessary the step
        will be repeated using a smaller step size until the user-defined
        error tolerance is matched. The actual step size taken is returned
        in @c hdid. The method returns 0 on success. Otherwise, an error
        code is returned. */
    ErrorCode nextRK(VecType& r_next, VecType& f_next, float& hdid);

    /** This method returns the next point of the field line compatible
        with a straight line approximation. The method subsequently
        produces samples on the field line using @c next(). If the number
        of samples exceeds @c nMax or an curvature-based error estimate
        exceeds @c tol the current sampling position is returned. @c tol
        is interpreted as an absolute error. If negative, @c tol is taken
        to be equal to @c hSampling. */
    int nextSL(VecType& r_next, VecType& f_next, int nMin, int nMax, float tol=-1);

    /** This method evaluates the right hand side of the ODE.
        The method returns 0 on success. Otherwise, an error
        code is returned. */
    inline ErrorCode eval(const VecType& r, VecType& f)
    {
        int error = rightHandSide(r,f,userData);
        if (error)
            return setError(ODE_DOMAINERROR);

        float length2 = f.dot(f);
        if (length2 == 0)
            return setError(ODE_ZEROVELOCITY);

        if (normalize)
            f *= orientation/sqrt(length2);
        else f *= orientation;

        return ODE_OK;
    }

    ///
    void freeze(const VecType& r);

    //@}

    ErrorCode setError(ErrorCode err) {
        error = err;
        return error;
    }

  private:
    float h;
    float hMin;
    float hMax;
    float hSampling;
    float tolerance;
    float orientation;

    // if 1, after a successful step hMin is compared to current step size hdid
    // returns with error code ODE_HMINREACHED if hdid < hMin
    int checkHMin;

    ErrorCode error;
    int normalize;
    Method method;
    void* userData;
    float s2, sStep;
    VecType r, f, r2, f2, d0, d1, d2, d3, df0, df1, df2, dff0, dff1;

    int (*rightHandSide)(const VecType& r, VecType& res, void*);

    ErrorCode rk21(VecType& r_next, VecType& f_next, VecType& err);
    ErrorCode rk32(VecType& r_next, VecType& f_next, VecType& err);
    ErrorCode rk43(VecType& r_next, VecType& f_next, VecType& err);
    ErrorCode rk54(VecType& r_next, VecType& f_next, VecType& err);
    ErrorCode rkck(VecType& r_next, VecType& f_next, VecType& err);

    float exponent(int idx);
    static int defaultRightHandSide(const VecType& r, VecType& f, void*);

    void initCubicPolynomial(float t1, VecType funcVal1, VecType deriv1,
                             float t2, VecType funcVal2, VecType deriv2,
                             float evalStart, float evalSampling);

    void nextCubicPolynomialStep();

    ErrorCode doRungeKutta(VecType& r_next, VecType& f_next, VecType& err);

    void adjustStepSizeH(float lastError);
};

template<class VecType>
float McODE<VecType>::exponent(int idx) {
    const float exponentVals[] = { 1.0f/2.0f, 1.0f/3.0f, 1.0f/4.0f, 1.0f/5.0f, 1.0f/5.0f };
    return exponentVals[idx];
}

template<class VecType>
McODE<VecType>::McODE() :
            s2(0.0f),
            sStep(0.0f)
{
    h = 1;
    hMin = 0.1f;
    hMax = 10.0f;
    hSampling = 1;
    tolerance = 0.02f;
    orientation = 1;
    error = ODE_OK;
    normalize = 1;
    method = RK43;
    userData = this;
    rightHandSide = defaultRightHandSide;

    checkHMin=0;
}

template<class VecType>
int McODE<VecType>::defaultRightHandSide(const VecType& r, VecType& f, void*)
{
    f = 0.5*r;
    f[0] = -r[1];
    f[1] = r[0];

    return 0;
}

template<class VecType>
void McODE<VecType>::setMethod(Method method)
{
    this->method = method;
}

template<class VecType>
void McODE<VecType>::setHMinMax(float hMin, float hMax)
{
    this->hMin = hMin;
    this->hMax = hMax;
}

template<class VecType>
void McODE<VecType>::setNormalization(int normalize)
{
    this->normalize = normalize;
}

template<class VecType>
void McODE<VecType>::setHSampling(float hSampling)
{
    this->hSampling = hSampling;
}

template<class VecType>
void McODE<VecType>::setTolerance(float tolerance)
{
    this->tolerance = tolerance;
}

template<class VecType>
void McODE<VecType>::setOrientation(float orientation)
{
    this->orientation = orientation;
}

template<class VecType>
void McODE<VecType>::setRightHandSide(int (*f)(const VecType& r, VecType& f, void*),
    void* userData)
{
    this->rightHandSide = f;
    this->userData = userData;
}

template<class VecType>
void McODE<VecType>::setCheckHMin(int setTo)
{
        checkHMin = setTo;
}

template<class VecType>
void McODE<VecType>::init(const VecType& r0, float hTry)
{
    setError(eval(r0,f));
    if (getErrorState() != ODE_OK) return;

    d0 = r2 = r = r0;
    df0 = f2 = f;
    s2 = 0;
    sStep = 0;
    error = ODE_OK;

    if (hTry<=0) {
        hTry = pow(tolerance,exponent(method));
        float len = f.length();
        if (len) hTry /= len;
        if (hTry>5*hSampling)
            hTry = 5*hSampling;
    }

    h = hTry;
}

template<class VecType>
typename McODE<VecType>::ErrorCode McODE<VecType>::next(VecType& rNext, int cont)
{
    VecType fNext;
    VecType ffNext;
    return next(rNext,fNext,ffNext,cont);
}

template<class VecType>
typename McODE<VecType>::ErrorCode McODE<VecType>::next(VecType& rNext, VecType& fNext, int cont)
{
    VecType ffNext;
    return next(rNext,fNext,ffNext, cont);
}

template<class VecType>
typename McODE<VecType>::ErrorCode McODE<VecType>::next(VecType& rNext, VecType& fNext, VecType& ffNext, int cont)
{
    if (error) {
        if (cont) {
            nextCubicPolynomialStep();
        }
        rNext = getPosition();
        fNext = getTangent();
        ffNext = getCurvature();
        return error;
    }

    if (next() != ODE_OK) {
        if (!cont) {
            d0 = r;
            df0 = f;
        }
    }

    rNext = getPosition();
    fNext = getTangent();
    ffNext = getCurvature();

    return error;
}

template<class VecType>
typename McODE<VecType>::ErrorCode McODE<VecType>::next()
{
    nextCubicPolynomialStep();

    if (error) return error;

    sStep += hSampling;

    if (sStep>s2) {
        VecType r1, f1;
        float s1;
        do {
            r = r1 = r2;
            f = f1 = f2;
            s1 = s2;

            float hdid;
            if (nextRK(r2, f2, hdid) != ODE_OK)
                return getErrorState();

            if (checkHMin && hdid < hMin)
                return setError(ODE_HMINREACHED);

            s2 += hdid;
        } while (sStep > s2);

        initCubicPolynomial(s1,r1,f1,s2,r2,f2,sStep,hSampling);
    }

    return ODE_OK;
}

template<class VecType>
void McODE<VecType>::initCubicPolynomial(float t1, VecType funcVal1, VecType deriv1,
                                         float t2, VecType funcVal2, VecType deriv2,
                                         float evalStart, float evalSampling)
{
    float dt = t2-t1;
    float t = (evalStart-t1)/dt;
    float u = evalSampling/dt;
    VecType ff1 = dt*deriv1;
    VecType ff2 = dt*deriv2;

    VecType a = 2*funcVal1 - 2*funcVal2 + ff1 + ff2;
    VecType b = -3*funcVal1 + 3*funcVal2 - 2*ff1 - ff2;
    VecType c = ff1;
    VecType d = funcVal1;

    VecType w0 = ((a*t+b)*t+c)*t+d;
    VecType w1 = (3*a*t+2*b)*t+c;
    VecType w2 = (3*a*t+b)*(u*u);
    VecType w3 = a*(u*u*u);

    d0 = w0;
    d1 = u*w1 + w2 + w3;
    d2 = 2*w2 + 6*w3;
    d3 = 6*w3;

    df0 = w1;
    df1 = u*(6*a*t+ 3*a*u+2*b);
    df2 = 6*a*u*u;

    dff0 = 6*a*t + 2*b;
    dff1 = 6*a*u;
}

template<class VecType>
void McODE<VecType>::nextCubicPolynomialStep()
{
    d0 += d1;
    d1 += d2;
    d2 += d3;
    df0 += df1;
    df1 += df2;
    dff0 += dff1;
}

template<class VecType>
typename McODE<VecType>::ErrorCode McODE<VecType>::nextRK(VecType& r_next, VecType& f_next, float& hdid)
{
    while (1) {
        VecType err;

        for (int nTry=0; ; nTry++, h*=0.25) {
            ErrorCode errorCode = doRungeKutta(r_next,f_next,err);
            if (errorCode == ODE_OK) break;
            if (h<hMin) return setError(errorCode);
            setError(ODE_OK);
        }

        // Local error criterium
        float norm = err.length();

        if (norm > tolerance) { // Last step ok ?
            if (h < hMin)
                return setError(ODE_HMINREACHED);

            adjustStepSizeH(norm);
        } else {
            hdid = h;
            r = r_next;
            f = f_next;

            adjustStepSizeH(norm);

            return ODE_OK;
        }
    }
}

template<class VecType>
void McODE<VecType>::adjustStepSizeH(float lastError)
{
    float factor;
    if (lastError > 0) {
        factor = pow((float)(0.8*tolerance/lastError), exponent(method));
        factor = MC_CLAMP(factor,0.5,2.0);
    } else factor = 2;

    h *= factor;

    if (h > hMax)
        h = hMax;
}

template<class VecType>
typename McODE<VecType>::ErrorCode McODE<VecType>::doRungeKutta(VecType& r_next, VecType& f_next, VecType& err)
{
    switch (method) {
    case RK21:
            return rk21(r_next, f_next, err);
    case RK32:
            return rk32(r_next, f_next, err);
    case RK43:
            return rk43(r_next, f_next, err);
    case RK54:
            return rk54(r_next, f_next, err);
    case RKCK:
            return rkck(r_next, f_next, err);
    }

    return setError(ODE_UNKNOWNMETHOD);
}

template<class VecType>
typename McODE<VecType>::ErrorCode McODE<VecType>::rk21(VecType& rnew, VecType& fnew, VecType& err)
{
    ErrorCode ret;
    VecType k,rtmp;

    rtmp = r + 0.5f*h*f;
    ret = eval(rtmp, k);
    if (ret) return ret;

    rnew = r + h*k;
    ret = eval(rnew, fnew);
    if (ret) return ret;

    err = h*(k-f);
    return ODE_OK;
}

template<class VecType>
typename McODE<VecType>::ErrorCode McODE<VecType>::rk32(VecType& rnew, VecType& fnew, VecType& err)
{
    ErrorCode ret;
    VecType k2,k3,rtmp;

    rtmp = r + 0.5f*h*f;
    ret = eval(rtmp, k2);
    if (ret) return ret;

    rtmp = r + 3.0f/4.0f*h*k2;
    ret = eval(rtmp, k3);
    if (ret) return ret;

    rnew = r + h*( 2.0f/9.0f*f + 1.0f/3.0f*k2 + 4.0f/9.0f*k3 );
    ret = eval(rnew, fnew);
    if (ret) return ret;

    rtmp = r + h*( 7.0f/24.0f*f + 1.0f/4.0f*k2 + 1.0f/3.0f*k3 + 1.0f/8.0f*fnew );
    err = rnew - rtmp;
    return ODE_OK;
}

template<class VecType>
typename McODE<VecType>::ErrorCode McODE<VecType>::rk43(VecType& rnew, VecType& fnew, VecType& err)
{
    ErrorCode ret;
    VecType k2,k3,k4,rtmp;

    rtmp = r + 0.5f*h*f;
    ret = eval(rtmp, k2);
    if (ret) return ret;

    rtmp = r + 0.5f*h*k2;
    ret = eval(rtmp, k3);
    if (ret) return ret;

    rtmp = r + h*k3;
    ret = eval(rtmp, k4);
    if (ret) return ret;

    rnew = r + h*( (f + k4)/6 + (k2 + k3)/3 );
    ret = eval(rnew, fnew);
    if (ret) return ret;

    err = h * (k4 - fnew)/6;
    return ODE_OK;
}

template<class VecType>
typename McODE<VecType>::ErrorCode McODE<VecType>::rk54(VecType& rnew, VecType& fnew, VecType& err)
{
    const float a21=0.2f, a31=3.0f/40.0f, a32= 9.0f/40.0f, a41=44.0f/45.0f,
        a42=-56.0f/15.0f, a43=32.0f/9.0f, a51=19372.0f/6561.0f, a52=-25360.0f/2187.0f,
        a53=64448.0f/6561.0f, a54=-212.0f/729.0f, a61=9017.0f/3168.0f, a62=-355.0f/33.0f,
        a63=46732.0f/5247.0f, a64=49.0f/176.0f, a65=-5103.0f/18656.0f, c1=35.0f/384.0f,
        c3=500.0f/1113.0f, c4=125.0f/192.0f, c5=-2187.0f/6784.0f, c6=11.0f/84.0f,
        dc1=c1-5179.0f/57600.0f, dc3=c3-7571.0f/16695.0f, dc4=c4-393.0f/640.0f,
        dc5=c5+92097.0f/339200.0f, dc6=c6-187.0f/2100.0f, dc7=-1.0f/40.0f;

    ErrorCode ret;
    VecType k2,k3,k4,k5,k6,rtmp;

    rtmp = r + h * a21*f;
    ret = eval(rtmp, k2);
    if (ret) return ret;

    rtmp = r + h * (a31*f + a32*k2);
    ret = eval(rtmp, k3);
    if (ret) return ret;

    rtmp = r + h * (a41*f + a42*k2 + a43*k3);
    ret = eval(rtmp, k4);
    if (ret) return ret;

    rtmp = r + h * (a51*f + a52*k2 + a53*k3 + a54*k4);
    ret = eval(rtmp, k5);
    if (ret) return ret;

    rtmp = r + h * (a61*f + a62*k2 + a63*k3 + a64*k4 + a65*k5);
    ret = eval(rtmp, k6);
    if (ret) return ret;

    rnew = r + h * (c1*f + c3*k3 + c4*k4 + c5*k5 + c6*k6);
    ret = eval(rnew, fnew);
    if (ret) return ret;

    err = h * (dc1*f + dc3*k3 + dc4*k4 + dc5*k5 + dc6*k6 + dc7*fnew);
    return ODE_OK;
}

template<class VecType>
typename McODE<VecType>::ErrorCode McODE<VecType>::rkck(VecType& rnew, VecType& fnew, VecType& err)
{
    const float b21=0.2f, b31=3.0f/40.0f, b32=9.0f/40.0f, b41=0.3f, b42=-0.9f, b43=1.2f,
        b51=-11.0f/54.0f, b52=2.5, b53=-70.0f/27.0f, b54=35.0f/27.0f, b61=1631.0f/55296.0f,
        b62=175.0f/512.0f, b63=575.0f/13824.0f, b64=44275.0f/110592.0f, b65=253.0f/4096.0f,
        c1=37.0f/378.0f, c3=250.0f/621.0f, c4=125.0f/594.0f, c6=512.0f/1771.0f,
        dc5=-277.0f/14336.0f, dc1=c1-2825.0f/27648.0f, dc3=c3-18575.0f/48384.0f,
        dc4=c4-13525.0f/55296.0f, dc6=c6-0.25f;

    ErrorCode ret;
    VecType ak2,ak3,ak4,ak5,ak6,rtmp;

    rtmp = r + h*b21*f;
    ret = eval(rtmp, ak2);
    if (ret) return ret;

    rtmp = r + h*(b31*f + b32*ak2);
    ret = eval(rtmp, ak3);
    if (ret) return ret;

    rtmp = r + h*(b41*f + b42*ak2 + b43*ak3);
    ret = eval(rtmp, ak4);
    if (ret) return ret;

    rtmp = r + h*(b51*f + b52*ak2 + b53*ak3 + b54*ak4);
    ret = eval(rtmp, ak5);
    if (ret) return ret;

    rtmp = r + h*(b61*f + b62*ak2 + b63*ak3 + b64*ak4 + b65*ak5);
    ret = eval(rtmp, ak6);
    if (ret) return ret;

    ret = eval(rnew, fnew);
    if (ret) return ret;

    rnew = r + h*(c1*f + c3*ak3 + c4*ak4 + c6*ak6);
    err = h * (dc1*f + dc3*ak3 + dc4*ak4 + dc5*ak5 + dc6*ak6);
    return ODE_OK;
}

template<class VecType>
int McODE<VecType>::nextSL(VecType& r, VecType& f, int nMin, int nMax, float tol)
{
    int i;
    VecType ff;
    float maxff = 0;
    float distance = 0;
    if (tol<=0)
        tol = 0.1f*hSampling;

    for (i=0; i<nMax; i++) {
        if (next(r,f,ff))
            return i;
        float fflen = ff.length();
        if (fflen > maxff)
            maxff = fflen;
        distance += hSampling;

        if (i>=nMin && distance*distance*maxff/8>tol)
            break;
    }

    return i;
}

template<class VecType>
void McODE<VecType>::freeze(const VecType& r0)
{
    d0 = r = r0;
    error = ODE_DOMAINERROR;
}

#endif


/// @}
