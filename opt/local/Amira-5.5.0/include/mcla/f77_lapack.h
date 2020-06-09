/*

    mcla is a wrapper library for freely-available LAPACK implementations.

    From the LAPACK Frequently Asked Questions (http://www.netlib.org/lapack/faq.html):

    LAPACK is a freely-available software package. It is available
    from netlib via anonymous ftp and the World Wide Web. Thus, it
    can be included in commercial software packages (and has
    been). We only ask that proper credit be given to the authors.

    Like all software, it is copyrighted. It is not trademarked,
    but we do ask the following:

    If you modify the source for these routines we ask that you
    change the name of the routine and comment the changes made to
    the original.

    We will gladly answer any questions regarding the software. If
    a modification is done, however, it is the responsibility of
    the person who modified the routine to provide support.

*/

/// @addtogroup mcla mcla
/// @{
#ifndef F77_LAPACK_H
#define F77_LAPACK_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MCLA_STRUCT_COMPLEX
#define MCLA_STRUCT_COMPLEX

struct complex_float {
    float re;
    float im;
};

struct complex_double {
    double re;
    double im;
};

#endif

#include "mclaAPI.h"

void MCLA_API f77_cbdsqr(
    const char & uplo,
    const int & n,
    const int & ncvt,
    const int & nru,
    const int & ncc,
    float * d,
    float * e,
    complex_float * vt,
    const int & ldvt,
    complex_float * u,
    const int & ldu,
    complex_float * c,
    const int & ldc,
    float * rwork,
    int & info
);

void MCLA_API f77_cgbbrd(
    const char & vect,
    const int & m,
    const int & n,
    const int & ncc,
    const int & kl,
    const int & ku,
    complex_float * ab,
    const int & ldab,
    float * d,
    float * e,
    complex_float * q,
    const int & ldq,
    complex_float * pt,
    const int & ldpt,
    complex_float * c,
    const int & ldc,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cgbcon(
    const char & norm,
    const int & n,
    const int & kl,
    const int & ku,
    const complex_float * ab,
    const int & ldab,
    const int * ipiv,
    const float & anorm,
    float & rcond,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cgbequ(
    const int & m,
    const int & n,
    const int & kl,
    const int & ku,
    const complex_float * ab,
    const int & ldab,
    float * r,
    float * c,
    float & rowcnd,
    float & colcnd,
    float & amax,
    int & info
);

void MCLA_API f77_cgbrfs(
    const char & trans,
    const int & n,
    const int & kl,
    const int & ku,
    const int & nrhs,
    const complex_float * ab,
    const int & ldab,
    const complex_float * afb,
    const int & ldafb,
    const int * ipiv,
    const complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cgbsv(
    const int & n,
    const int & kl,
    const int & ku,
    const int & nrhs,
    complex_float * ab,
    const int & ldab,
    int * ipiv,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_cgbsvx(
    const char & fact,
    const char & trans,
    const int & n,
    const int & kl,
    const int & ku,
    const int & nrhs,
    complex_float * ab,
    const int & ldab,
    complex_float * afb,
    const int & ldafb,
    int * ipiv,
    char & equed,
    float * r,
    float * c,
    complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cgbtrf(
    const int & m,
    const int & n,
    const int & kl,
    const int & ku,
    complex_float * ab,
    const int & ldab,
    int * ipiv,
    int & info
);

void MCLA_API f77_cgbtrs(
    const char & trans,
    const int & n,
    const int & kl,
    const int & ku,
    const int & nrhs,
    const complex_float * ab,
    const int & ldab,
    const int * ipiv,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_cgebak(
    const char & job,
    const char & side,
    const int & n,
    const int & ilo,
    const int & ihi,
    const float * scale,
    const int & m,
    complex_float * v,
    const int & ldv,
    int & info
);

void MCLA_API f77_cgebal(
    const char & job,
    const int & n,
    complex_float * a,
    const int & lda,
    int & ilo,
    int & ihi,
    float * scale,
    int & info
);

void MCLA_API f77_cgebrd(
    const int & m,
    const int & n,
    complex_float * a,
    const int & lda,
    float * d,
    float * e,
    complex_float * tauq,
    complex_float * taup,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cgecon(
    const char & norm,
    const int & n,
    const complex_float * a,
    const int & lda,
    const float & anorm,
    float & rcond,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cgeequ(
    const int & m,
    const int & n,
    const complex_float * a,
    const int & lda,
    float * r,
    float * c,
    float & rowcnd,
    float & colcnd,
    float & amax,
    int & info
);

void MCLA_API f77_cgees(
    const char & jobvs,
    const char & sort,
    int (* select)(...),
    const int & n,
    complex_float * a,
    const int & lda,
    int & sdim,
    complex_float * w,
    complex_float * vs,
    const int & ldvs,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int * bwork,
    int & info
);

void MCLA_API f77_cgeesx(
    const char & jobvs,
    const char & sort,
    int (* select)(...),
    const char & sense,
    const int & n,
    complex_float * a,
    const int & lda,
    int & sdim,
    complex_float * w,
    complex_float * vs,
    const int & ldvs,
    float & rconde,
    float & rcondv,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int * bwork,
    int & info
);

void MCLA_API f77_cgeev(
    const char & jobvl,
    const char & jobvr,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * w,
    complex_float * vl,
    const int & ldvl,
    complex_float * vr,
    const int & ldvr,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int & info
);

void MCLA_API f77_cgeevx(
    const char & balanc,
    const char & jobvl,
    const char & jobvr,
    const char & sense,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * w,
    complex_float * vl,
    const int & ldvl,
    complex_float * vr,
    const int & ldvr,
    int & ilo,
    int & ihi,
    float * scale,
    float & abnrm,
    float * rconde,
    float * rcondv,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int & info
);

void MCLA_API f77_cgehrd(
    const int & n,
    const int & ilo,
    const int & ihi,
    complex_float * a,
    const int & lda,
    complex_float * tau,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cgelqf(
    const int & m,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * tau,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cgels(
    const char & trans,
    const int & m,
    const int & n,
    const int & nrhs,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cgelsd(
    const int & m,
    const int & n,
    const int & nrhs,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    float * s,
    const float & rcond,
    int & rank,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int * iwork,
    int & info
);

void MCLA_API f77_cgelss(
    const int & m,
    const int & n,
    const int & nrhs,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    float * s,
    const float & rcond,
    int & rank,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int & info
);

void MCLA_API f77_cgelsy(
    const int & m,
    const int & n,
    const int & nrhs,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    int * jpvt,
    const float & rcond,
    int & rank,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int & info
);

void MCLA_API f77_cgeqlf(
    const int & m,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * tau,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cgeqp3(
    const int & m,
    const int & n,
    complex_float * a,
    const int & lda,
    int * jpvt,
    complex_float * tau,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int & info
);

void MCLA_API f77_cgeqrf(
    const int & m,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * tau,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cgerfs(
    const char & trans,
    const int & n,
    const int & nrhs,
    const complex_float * a,
    const int & lda,
    const complex_float * af,
    const int & ldaf,
    const int * ipiv,
    const complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cgerqf(
    const int & m,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * tau,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cgesdd(
    const char & jobz,
    const int & m,
    const int & n,
    complex_float * a,
    const int & lda,
    float * s,
    complex_float * u,
    const int & ldu,
    complex_float * vt,
    const int & ldvt,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int * iwork,
    int & info
);

void MCLA_API f77_cgesv(
    const int & n,
    const int & nrhs,
    complex_float * a,
    const int & lda,
    int * ipiv,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_cgesvd(
    const char & jobu,
    const char & jobvt,
    const int & m,
    const int & n,
    complex_float * a,
    const int & lda,
    float * s,
    complex_float * u,
    const int & ldu,
    complex_float * vt,
    const int & ldvt,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int & info
);

void MCLA_API f77_cgesvx(
    const char & fact,
    const char & trans,
    const int & n,
    const int & nrhs,
    complex_float * a,
    const int & lda,
    complex_float * af,
    const int & ldaf,
    int * ipiv,
    char & equed,
    float * r,
    float * c,
    complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cgetrf(
    const int & m,
    const int & n,
    complex_float * a,
    const int & lda,
    int * ipiv,
    int & info
);

void MCLA_API f77_cgetri(
    const int & n,
    complex_float * a,
    const int & lda,
    const int * ipiv,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cgetrs(
    const char & trans,
    const int & n,
    const int & nrhs,
    const complex_float * a,
    const int & lda,
    const int * ipiv,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_cggbak(
    const char & job,
    const char & side,
    const int & n,
    const int & ilo,
    const int & ihi,
    const float * lscale,
    const float * rscale,
    const int & m,
    complex_float * v,
    const int & ldv,
    int & info
);

void MCLA_API f77_cggbal(
    const char & job,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    int & ilo,
    int & ihi,
    float * lscale,
    float * rscale,
    float * work,
    int & info
);

void MCLA_API f77_cgges(
    const char & jobvsl,
    const char & jobvsr,
    const char & sort,
    int (* selctg)(...),
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    int & sdim,
    complex_float * alpha,
    complex_float * beta,
    complex_float * vsl,
    const int & ldvsl,
    complex_float * vsr,
    const int & ldvsr,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int * bwork,
    int & info
);

void MCLA_API f77_cggesx(
    const char & jobvsl,
    const char & jobvsr,
    const char & sort,
    int (* selctg)(...),
    const char & sense,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    int & sdim,
    complex_float * alpha,
    complex_float * beta,
    complex_float * vsl,
    const int & ldvsl,
    complex_float * vsr,
    const int & ldvsr,
    float * rconde,
    float * rcondv,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int * iwork,
    const int & liwork,
    int * bwork,
    int & info
);

void MCLA_API f77_cggev(
    const char & jobvl,
    const char & jobvr,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    complex_float * alpha,
    complex_float * beta,
    complex_float * vl,
    const int & ldvl,
    complex_float * vr,
    const int & ldvr,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int & info
);

void MCLA_API f77_cggevx(
    const char & balanc,
    const char & jobvl,
    const char & jobvr,
    const char & sense,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    complex_float * alpha,
    complex_float * beta,
    complex_float * vl,
    const int & ldvl,
    complex_float * vr,
    const int & ldvr,
    int & ilo,
    int & ihi,
    float * lscale,
    float * rscale,
    float & abnrm,
    float & bbnrm,
    float * rconde,
    float * rcondv,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int * iwork,
    int * bwork,
    int & info
);

void MCLA_API f77_cggglm(
    const int & n,
    const int & m,
    const int & p,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    complex_float * d,
    complex_float * x,
    complex_float * y,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cgghrd(
    const char & compq,
    const char & compz,
    const int & n,
    const int & ilo,
    const int & ihi,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    complex_float * q,
    const int & ldq,
    complex_float * z,
    const int & ldz,
    int & info
);

void MCLA_API f77_cgglse(
    const int & m,
    const int & n,
    const int & p,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    complex_float * c,
    complex_float * d,
    complex_float * x,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cggqrf(
    const int & n,
    const int & m,
    const int & p,
    complex_float * a,
    const int & lda,
    complex_float * taua,
    complex_float * b,
    const int & ldb,
    complex_float * taub,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cggrqf(
    const int & m,
    const int & p,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * taua,
    complex_float * b,
    const int & ldb,
    complex_float * taub,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cggsvd(
    const char & jobu,
    const char & jobv,
    const char & jobq,
    const int & m,
    const int & n,
    const int & p,
    int & k,
    int & l,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    float * alpha,
    float * beta,
    complex_float * u,
    const int & ldu,
    complex_float * v,
    const int & ldv,
    complex_float * q,
    const int & ldq,
    complex_float * work,
    float * rwork,
    int * iwork,
    int & info
);

void MCLA_API f77_cggsvp(
    const char & jobu,
    const char & jobv,
    const char & jobq,
    const int & m,
    const int & p,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    const float & tola,
    const float & tolb,
    int & k,
    int & l,
    complex_float * u,
    const int & ldu,
    complex_float * v,
    const int & ldv,
    complex_float * q,
    const int & ldq,
    int * iwork,
    float * rwork,
    complex_float * tau,
    complex_float * work,
    int & info
);

void MCLA_API f77_cgtcon(
    const char & norm,
    const int & n,
    const complex_float * dl,
    const complex_float * d,
    const complex_float * du,
    const complex_float * du2,
    const int * ipiv,
    const float & anorm,
    float & rcond,
    complex_float * work,
    int & info
);

void MCLA_API f77_cgtrfs(
    const char & trans,
    const int & n,
    const int & nrhs,
    const complex_float * dl,
    const complex_float * d,
    const complex_float * du,
    const complex_float * dlf,
    const complex_float * df,
    const complex_float * duf,
    const complex_float * du2,
    const int * ipiv,
    const complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cgtsv(
    const int & n,
    const int & nrhs,
    complex_float * dl,
    complex_float * d,
    complex_float * du,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_cgtsvx(
    const char & fact,
    const char & trans,
    const int & n,
    const int & nrhs,
    const complex_float * dl,
    const complex_float * d,
    const complex_float * du,
    complex_float * dlf,
    complex_float * df,
    complex_float * duf,
    complex_float * du2,
    int * ipiv,
    const complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cgttrf(
    const int & n,
    complex_float * dl,
    complex_float * d,
    complex_float * du,
    complex_float * du2,
    int * ipiv,
    int & info
);

void MCLA_API f77_cgttrs(
    const char & trans,
    const int & n,
    const int & nrhs,
    const complex_float * dl,
    const complex_float * d,
    const complex_float * du,
    const complex_float * du2,
    const int * ipiv,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_chbev(
    const char & jobz,
    const char & uplo,
    const int & n,
    const int & kd,
    complex_float * ab,
    const int & ldab,
    float * w,
    complex_float * z,
    const int & ldz,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_chbevd(
    const char & jobz,
    const char & uplo,
    const int & n,
    const int & kd,
    complex_float * ab,
    const int & ldab,
    float * w,
    complex_float * z,
    const int & ldz,
    complex_float * work,
    const int & lwork,
    float * rwork,
    const int & lrwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_chbevx(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    const int & kd,
    complex_float * ab,
    const int & ldab,
    complex_float * q,
    const int & ldq,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    complex_float * z,
    const int & ldz,
    complex_float * work,
    float * rwork,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_chbgst(
    const char & vect,
    const char & uplo,
    const int & n,
    const int & ka,
    const int & kb,
    complex_float * ab,
    const int & ldab,
    const complex_float * bb,
    const int & ldbb,
    complex_float * x,
    const int & ldx,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_chbgv(
    const char & jobz,
    const char & uplo,
    const int & n,
    const int & ka,
    const int & kb,
    complex_float * ab,
    const int & ldab,
    complex_float * bb,
    const int & ldbb,
    float * w,
    complex_float * z,
    const int & ldz,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_chbgvd(
    const char & jobz,
    const char & uplo,
    const int & n,
    const int & ka,
    const int & kb,
    complex_float * ab,
    const int & ldab,
    complex_float * bb,
    const int & ldbb,
    float * w,
    complex_float * z,
    const int & ldz,
    complex_float * work,
    const int & lwork,
    float * rwork,
    const int & lrwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_chbgvx(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    const int & ka,
    const int & kb,
    complex_float * ab,
    const int & ldab,
    complex_float * bb,
    const int & ldbb,
    complex_float * q,
    const int & ldq,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    complex_float * z,
    const int & ldz,
    complex_float * work,
    float * rwork,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_chbtrd(
    const char & vect,
    const char & uplo,
    const int & n,
    const int & kd,
    complex_float * ab,
    const int & ldab,
    float * d,
    float * e,
    complex_float * q,
    const int & ldq,
    complex_float * work,
    int & info
);

void MCLA_API f77_checon(
    const char & uplo,
    const int & n,
    const complex_float * a,
    const int & lda,
    const int * ipiv,
    const float & anorm,
    float & rcond,
    complex_float * work,
    int & info
);

void MCLA_API f77_cheev(
    const char & jobz,
    const char & uplo,
    const int & n,
    complex_float * a,
    const int & lda,
    float * w,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int & info
);

void MCLA_API f77_cheevd(
    const char & jobz,
    const char & uplo,
    const int & n,
    complex_float * a,
    const int & lda,
    float * w,
    complex_float * work,
    const int & lwork,
    float * rwork,
    const int & lrwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_cheevr(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    complex_float * a,
    const int & lda,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    complex_float * z,
    const int & ldz,
    int * isuppz,
    complex_float * work,
    const int & lwork,
    float * rwork,
    const int & lrwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_cheevx(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    complex_float * a,
    const int & lda,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    complex_float * z,
    const int & ldz,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_chegst(
    const int & itype,
    const char & uplo,
    const int & n,
    complex_float * a,
    const int & lda,
    const complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_chegv(
    const int & itype,
    const char & jobz,
    const char & uplo,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    float * w,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int & info
);

void MCLA_API f77_chegvd(
    const int & itype,
    const char & jobz,
    const char & uplo,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    float * w,
    complex_float * work,
    const int & lwork,
    float * rwork,
    const int & lrwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_chegvx(
    const int & itype,
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    complex_float * z,
    const int & ldz,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_cherfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_float * a,
    const int & lda,
    const complex_float * af,
    const int & ldaf,
    const int * ipiv,
    const complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_chesv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    complex_float * a,
    const int & lda,
    int * ipiv,
    complex_float * b,
    const int & ldb,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_chesvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_float * a,
    const int & lda,
    complex_float * af,
    const int & ldaf,
    int * ipiv,
    const complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int & info
);

void MCLA_API f77_chetrd(
    const char & uplo,
    const int & n,
    complex_float * a,
    const int & lda,
    float * d,
    float * e,
    complex_float * tau,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_chetrf(
    const char & uplo,
    const int & n,
    complex_float * a,
    const int & lda,
    int * ipiv,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_chetri(
    const char & uplo,
    const int & n,
    complex_float * a,
    const int & lda,
    const int * ipiv,
    complex_float * work,
    int & info
);

void MCLA_API f77_chetrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_float * a,
    const int & lda,
    const int * ipiv,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_chgeqz(
    const char & job,
    const char & compq,
    const char & compz,
    const int & n,
    const int & ilo,
    const int & ihi,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    complex_float * alpha,
    complex_float * beta,
    complex_float * q,
    const int & ldq,
    complex_float * z,
    const int & ldz,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int & info
);

void MCLA_API f77_chpcon(
    const char & uplo,
    const int & n,
    const complex_float * ap,
    const int * ipiv,
    const float & anorm,
    float & rcond,
    complex_float * work,
    int & info
);

void MCLA_API f77_chpev(
    const char & jobz,
    const char & uplo,
    const int & n,
    complex_float * ap,
    float * w,
    complex_float * z,
    const int & ldz,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_chpevd(
    const char & jobz,
    const char & uplo,
    const int & n,
    complex_float * ap,
    float * w,
    complex_float * z,
    const int & ldz,
    complex_float * work,
    const int & lwork,
    float * rwork,
    const int & lrwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_chpevx(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    complex_float * ap,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    complex_float * z,
    const int & ldz,
    complex_float * work,
    float * rwork,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_chpgst(
    const int & itype,
    const char & uplo,
    const int & n,
    complex_float * ap,
    const complex_float * bp,
    int & info
);

void MCLA_API f77_chpgv(
    const int & itype,
    const char & jobz,
    const char & uplo,
    const int & n,
    complex_float * ap,
    complex_float * bp,
    float * w,
    complex_float * z,
    const int & ldz,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_chpgvd(
    const int & itype,
    const char & jobz,
    const char & uplo,
    const int & n,
    complex_float * ap,
    complex_float * bp,
    float * w,
    complex_float * z,
    const int & ldz,
    complex_float * work,
    const int & lwork,
    float * rwork,
    const int & lrwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_chpgvx(
    const int & itype,
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    complex_float * ap,
    complex_float * bp,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    complex_float * z,
    const int & ldz,
    complex_float * work,
    float * rwork,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_chprfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_float * ap,
    const complex_float * afp,
    const int * ipiv,
    const complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_chpsv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    complex_float * ap,
    int * ipiv,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_chpsvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_float * ap,
    complex_float * afp,
    int * ipiv,
    const complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_chptrd(
    const char & uplo,
    const int & n,
    complex_float * ap,
    float * d,
    float * e,
    complex_float * tau,
    int & info
);

void MCLA_API f77_chptrf(
    const char & uplo,
    const int & n,
    complex_float * ap,
    int * ipiv,
    int & info
);

void MCLA_API f77_chptri(
    const char & uplo,
    const int & n,
    complex_float * ap,
    const int * ipiv,
    complex_float * work,
    int & info
);

void MCLA_API f77_chptrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_float * ap,
    const int * ipiv,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_chsein(
    const char & side,
    const char & eigsrc,
    const char & initv,
    const int * select,
    const int & n,
    const complex_float * h,
    const int & ldh,
    complex_float * w,
    complex_float * vl,
    const int & ldvl,
    complex_float * vr,
    const int & ldvr,
    const int & mm,
    int & m,
    complex_float * work,
    float * rwork,
    int * ifaill,
    int * ifailr,
    int & info
);

void MCLA_API f77_chseqr(
    const char & job,
    const char & compz,
    const int & n,
    const int & ilo,
    const int & ihi,
    complex_float * h,
    const int & ldh,
    complex_float * w,
    complex_float * z,
    const int & ldz,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cpbcon(
    const char & uplo,
    const int & n,
    const int & kd,
    const complex_float * ab,
    const int & ldab,
    const float & anorm,
    float & rcond,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cpbequ(
    const char & uplo,
    const int & n,
    const int & kd,
    const complex_float * ab,
    const int & ldab,
    float * s,
    float & scond,
    float & amax,
    int & info
);

void MCLA_API f77_cpbrfs(
    const char & uplo,
    const int & n,
    const int & kd,
    const int & nrhs,
    const complex_float * ab,
    const int & ldab,
    const complex_float * afb,
    const int & ldafb,
    const complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cpbstf(
    const char & uplo,
    const int & n,
    const int & kd,
    complex_float * ab,
    const int & ldab,
    int & info
);

void MCLA_API f77_cpbsv(
    const char & uplo,
    const int & n,
    const int & kd,
    const int & nrhs,
    complex_float * ab,
    const int & ldab,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_cpbsvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & kd,
    const int & nrhs,
    complex_float * ab,
    const int & ldab,
    complex_float * afb,
    const int & ldafb,
    char & equed,
    float * s,
    complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cpbtrf(
    const char & uplo,
    const int & n,
    const int & kd,
    complex_float * ab,
    const int & ldab,
    int & info
);

void MCLA_API f77_cpbtrs(
    const char & uplo,
    const int & n,
    const int & kd,
    const int & nrhs,
    const complex_float * ab,
    const int & ldab,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_cpocon(
    const char & uplo,
    const int & n,
    const complex_float * a,
    const int & lda,
    const float & anorm,
    float & rcond,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cpoequ(
    const int & n,
    const complex_float * a,
    const int & lda,
    float * s,
    float & scond,
    float & amax,
    int & info
);

void MCLA_API f77_cporfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_float * a,
    const int & lda,
    const complex_float * af,
    const int & ldaf,
    const complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cposv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_cposvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    complex_float * a,
    const int & lda,
    complex_float * af,
    const int & ldaf,
    char & equed,
    float * s,
    complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cpotrf(
    const char & uplo,
    const int & n,
    complex_float * a,
    const int & lda,
    int & info
);

void MCLA_API f77_cpotri(
    const char & uplo,
    const int & n,
    complex_float * a,
    const int & lda,
    int & info
);

void MCLA_API f77_cpotrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_cppcon(
    const char & uplo,
    const int & n,
    const complex_float * ap,
    const float & anorm,
    float & rcond,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cppequ(
    const char & uplo,
    const int & n,
    const complex_float * ap,
    float * s,
    float & scond,
    float & amax,
    int & info
);

void MCLA_API f77_cpprfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_float * ap,
    const complex_float * afp,
    const complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cppsv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    complex_float * ap,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_cppsvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    complex_float * ap,
    complex_float * afp,
    char & equed,
    float * s,
    complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cpptrf(
    const char & uplo,
    const int & n,
    complex_float * ap,
    int & info
);

void MCLA_API f77_cpptri(
    const char & uplo,
    const int & n,
    complex_float * ap,
    int & info
);

void MCLA_API f77_cpptrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_float * ap,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_cptcon(
    const int & n,
    const float * d,
    const complex_float * e,
    const float & anorm,
    float & rcond,
    float * rwork,
    int & info
);

void MCLA_API f77_cpteqr(
    const char & compz,
    const int & n,
    float * d,
    float * e,
    complex_float * z,
    const int & ldz,
    float * work,
    int & info
);

void MCLA_API f77_cptrfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const float * d,
    const complex_float * e,
    const float * df,
    const complex_float * ef,
    const complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cptsv(
    const int & n,
    const int & nrhs,
    float * d,
    complex_float * e,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_cptsvx(
    const char & fact,
    const int & n,
    const int & nrhs,
    const float * d,
    const complex_float * e,
    float * df,
    complex_float * ef,
    const complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cpttrf(
    const int & n,
    float * d,
    complex_float * e,
    int & info
);

void MCLA_API f77_cpttrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const float * d,
    const complex_float * e,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_cspcon(
    const char & uplo,
    const int & n,
    const complex_float * ap,
    const int * ipiv,
    const float & anorm,
    float & rcond,
    complex_float * work,
    int & info
);

void MCLA_API f77_csprfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_float * ap,
    const complex_float * afp,
    const int * ipiv,
    const complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_cspsv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    complex_float * ap,
    int * ipiv,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_cspsvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_float * ap,
    complex_float * afp,
    int * ipiv,
    const complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_csptrf(
    const char & uplo,
    const int & n,
    complex_float * ap,
    int * ipiv,
    int & info
);

void MCLA_API f77_csptri(
    const char & uplo,
    const int & n,
    complex_float * ap,
    const int * ipiv,
    complex_float * work,
    int & info
);

void MCLA_API f77_csptrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_float * ap,
    const int * ipiv,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_cstedc(
    const char & compz,
    const int & n,
    float * d,
    float * e,
    complex_float * z,
    const int & ldz,
    complex_float * work,
    const int & lwork,
    float * rwork,
    const int & lrwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_cstegr(
    const char & jobz,
    const char & range,
    const int & n,
    float * d,
    float * e,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    complex_float * z,
    const int & ldz,
    int * isuppz,
    float * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_cstein(
    const int & n,
    const float * d,
    const float * e,
    const int & m,
    const float * w,
    const int * iblock,
    const int * isplit,
    complex_float * z,
    const int & ldz,
    float * work,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_csteqr(
    const char & compz,
    const int & n,
    float * d,
    float * e,
    complex_float * z,
    const int & ldz,
    float * work,
    int & info
);

void MCLA_API f77_csycon(
    const char & uplo,
    const int & n,
    const complex_float * a,
    const int & lda,
    const int * ipiv,
    const float & anorm,
    float & rcond,
    complex_float * work,
    int & info
);

void MCLA_API f77_csyrfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_float * a,
    const int & lda,
    const complex_float * af,
    const int & ldaf,
    const int * ipiv,
    const complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_csysv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    complex_float * a,
    const int & lda,
    int * ipiv,
    complex_float * b,
    const int & ldb,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_csysvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_float * a,
    const int & lda,
    complex_float * af,
    const int & ldaf,
    int * ipiv,
    const complex_float * b,
    const int & ldb,
    complex_float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    complex_float * work,
    const int & lwork,
    float * rwork,
    int & info
);

void MCLA_API f77_csytrf(
    const char & uplo,
    const int & n,
    complex_float * a,
    const int & lda,
    int * ipiv,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_csytri(
    const char & uplo,
    const int & n,
    complex_float * a,
    const int & lda,
    const int * ipiv,
    complex_float * work,
    int & info
);

void MCLA_API f77_csytrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_float * a,
    const int & lda,
    const int * ipiv,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_ctbcon(
    const char & norm,
    const char & uplo,
    const char & diag,
    const int & n,
    const int & kd,
    const complex_float * ab,
    const int & ldab,
    float & rcond,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_ctbrfs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & kd,
    const int & nrhs,
    const complex_float * ab,
    const int & ldab,
    const complex_float * b,
    const int & ldb,
    const complex_float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_ctbtrs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & kd,
    const int & nrhs,
    const complex_float * ab,
    const int & ldab,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_ctgevc(
    const char & side,
    const char & howmny,
    const int * select,
    const int & n,
    const complex_float * a,
    const int & lda,
    const complex_float * b,
    const int & ldb,
    complex_float * vl,
    const int & ldvl,
    complex_float * vr,
    const int & ldvr,
    const int & mm,
    int & m,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_ctgexc(
    const int & wantq,
    const int & wantz,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    complex_float * q,
    const int & ldq,
    complex_float * z,
    const int & ldz,
    int & ifst,
    int & ilst,
    int & info
);

void MCLA_API f77_ctgsen(
    const int & ijob,
    const int & wantq,
    const int & wantz,
    const int * select,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    complex_float * alpha,
    complex_float * beta,
    complex_float * q,
    const int & ldq,
    complex_float * z,
    const int & ldz,
    int & m,
    float & pl,
    float & pr,
    float * dif,
    complex_float * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_ctgsja(
    const char & jobu,
    const char & jobv,
    const char & jobq,
    const int & m,
    const int & p,
    const int & n,
    const int & k,
    const int & l,
    complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    const float & tola,
    const float & tolb,
    float * alpha,
    float * beta,
    complex_float * u,
    const int & ldu,
    complex_float * v,
    const int & ldv,
    complex_float * q,
    const int & ldq,
    complex_float * work,
    int & ncycle,
    int & info
);

void MCLA_API f77_ctgsna(
    const char & job,
    const char & howmny,
    const int * select,
    const int & n,
    const complex_float * a,
    const int & lda,
    const complex_float * b,
    const int & ldb,
    const complex_float * vl,
    const int & ldvl,
    const complex_float * vr,
    const int & ldvr,
    float * s,
    float * dif,
    const int & mm,
    int & m,
    complex_float * work,
    const int & lwork,
    int * iwork,
    int & info
);

void MCLA_API f77_ctgsyl(
    const char & trans,
    const int & ijob,
    const int & m,
    const int & n,
    const complex_float * a,
    const int & lda,
    const complex_float * b,
    const int & ldb,
    complex_float * c,
    const int & ldc,
    const complex_float * d,
    const int & ldd,
    const complex_float * e,
    const int & lde,
    complex_float * f,
    const int & ldf,
    float & scale,
    float & dif,
    complex_float * work,
    const int & lwork,
    int * iwork,
    int & info
);

void MCLA_API f77_ctpcon(
    const char & norm,
    const char & uplo,
    const char & diag,
    const int & n,
    const complex_float * ap,
    float & rcond,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_ctprfs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & nrhs,
    const complex_float * ap,
    const complex_float * b,
    const int & ldb,
    const complex_float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_ctptri(
    const char & uplo,
    const char & diag,
    const int & n,
    complex_float * ap,
    int & info
);

void MCLA_API f77_ctptrs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & nrhs,
    const complex_float * ap,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_ctrcon(
    const char & norm,
    const char & uplo,
    const char & diag,
    const int & n,
    const complex_float * a,
    const int & lda,
    float & rcond,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_ctrevc(
    const char & side,
    const char & howmny,
    const int * select,
    const int & n,
    complex_float * t,
    const int & ldt,
    complex_float * vl,
    const int & ldvl,
    complex_float * vr,
    const int & ldvr,
    const int & mm,
    int & m,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_ctrexc(
    const char & compq,
    const int & n,
    complex_float * t,
    const int & ldt,
    complex_float * q,
    const int & ldq,
    const int & ifst,
    const int & ilst,
    int & info
);

void MCLA_API f77_ctrrfs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & nrhs,
    const complex_float * a,
    const int & lda,
    const complex_float * b,
    const int & ldb,
    const complex_float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    complex_float * work,
    float * rwork,
    int & info
);

void MCLA_API f77_ctrsen(
    const char & job,
    const char & compq,
    const int * select,
    const int & n,
    complex_float * t,
    const int & ldt,
    complex_float * q,
    const int & ldq,
    complex_float * w,
    int & m,
    float & s,
    float & sep,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_ctrsna(
    const char & job,
    const char & howmny,
    const int * select,
    const int & n,
    const complex_float * t,
    const int & ldt,
    const complex_float * vl,
    const int & ldvl,
    const complex_float * vr,
    const int & ldvr,
    float * s,
    float * sep,
    const int & mm,
    int & m,
    complex_float * work,
    const int & ldwork,
    float * rwork,
    int & info
);

void MCLA_API f77_ctrsyl(
    const char & trana,
    const char & tranb,
    const int & isgn,
    const int & m,
    const int & n,
    const complex_float * a,
    const int & lda,
    const complex_float * b,
    const int & ldb,
    complex_float * c,
    const int & ldc,
    float & scale,
    int & info
);

void MCLA_API f77_ctrtri(
    const char & uplo,
    const char & diag,
    const int & n,
    complex_float * a,
    const int & lda,
    int & info
);

void MCLA_API f77_ctrtrs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & nrhs,
    const complex_float * a,
    const int & lda,
    complex_float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_ctzrzf(
    const int & m,
    const int & n,
    complex_float * a,
    const int & lda,
    complex_float * tau,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cungbr(
    const char & vect,
    const int & m,
    const int & n,
    const int & k,
    complex_float * a,
    const int & lda,
    const complex_float * tau,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cunghr(
    const int & n,
    const int & ilo,
    const int & ihi,
    complex_float * a,
    const int & lda,
    const complex_float * tau,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cunglq(
    const int & m,
    const int & n,
    const int & k,
    complex_float * a,
    const int & lda,
    const complex_float * tau,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cungql(
    const int & m,
    const int & n,
    const int & k,
    complex_float * a,
    const int & lda,
    const complex_float * tau,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cungqr(
    const int & m,
    const int & n,
    const int & k,
    complex_float * a,
    const int & lda,
    const complex_float * tau,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cungrq(
    const int & m,
    const int & n,
    const int & k,
    complex_float * a,
    const int & lda,
    const complex_float * tau,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cungtr(
    const char & uplo,
    const int & n,
    complex_float * a,
    const int & lda,
    const complex_float * tau,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cunmbr(
    const char & vect,
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const complex_float * a,
    const int & lda,
    const complex_float * tau,
    complex_float * c,
    const int & ldc,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cunmhr(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & ilo,
    const int & ihi,
    const complex_float * a,
    const int & lda,
    const complex_float * tau,
    complex_float * c,
    const int & ldc,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cunmlq(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const complex_float * a,
    const int & lda,
    const complex_float * tau,
    complex_float * c,
    const int & ldc,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cunmql(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const complex_float * a,
    const int & lda,
    const complex_float * tau,
    complex_float * c,
    const int & ldc,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cunmqr(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const complex_float * a,
    const int & lda,
    const complex_float * tau,
    complex_float * c,
    const int & ldc,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cunmrq(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const complex_float * a,
    const int & lda,
    const complex_float * tau,
    complex_float * c,
    const int & ldc,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cunmrz(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const int & l,
    const complex_float * a,
    const int & lda,
    const complex_float * tau,
    complex_float * c,
    const int & ldc,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cunmtr(
    const char & side,
    const char & uplo,
    const char & trans,
    const int & m,
    const int & n,
    const complex_float * a,
    const int & lda,
    const complex_float * tau,
    complex_float * c,
    const int & ldc,
    complex_float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_cupgtr(
    const char & uplo,
    const int & n,
    const complex_float * ap,
    const complex_float * tau,
    complex_float * q,
    const int & ldq,
    complex_float * work,
    int & info
);

void MCLA_API f77_cupmtr(
    const char & side,
    const char & uplo,
    const char & trans,
    const int & m,
    const int & n,
    const complex_float * ap,
    const complex_float * tau,
    complex_float * c,
    const int & ldc,
    complex_float * work,
    int & info
);

void MCLA_API f77_dbdsdc(
    const char & uplo,
    const char & compq,
    const int & n,
    double * d,
    double * e,
    double * u,
    const int & ldu,
    double * vt,
    const int & ldvt,
    double * q,
    int * iq,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dbdsqr(
    const char & uplo,
    const int & n,
    const int & ncvt,
    const int & nru,
    const int & ncc,
    double * d,
    double * e,
    double * vt,
    const int & ldvt,
    double * u,
    const int & ldu,
    double * c,
    const int & ldc,
    double * work,
    int & info
);

void MCLA_API f77_ddisna(
    const char & job,
    const int & m,
    const int & n,
    const double * d,
    double * sep,
    int & info
);

void MCLA_API f77_dgbbrd(
    const char & vect,
    const int & m,
    const int & n,
    const int & ncc,
    const int & kl,
    const int & ku,
    double * ab,
    const int & ldab,
    double * d,
    double * e,
    double * q,
    const int & ldq,
    double * pt,
    const int & ldpt,
    double * c,
    const int & ldc,
    double * work,
    int & info
);

void MCLA_API f77_dgbcon(
    const char & norm,
    const int & n,
    const int & kl,
    const int & ku,
    const double * ab,
    const int & ldab,
    const int * ipiv,
    const double & anorm,
    double & rcond,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dgbequ(
    const int & m,
    const int & n,
    const int & kl,
    const int & ku,
    const double * ab,
    const int & ldab,
    double * r,
    double * c,
    double & rowcnd,
    double & colcnd,
    double & amax,
    int & info
);

void MCLA_API f77_dgbrfs(
    const char & trans,
    const int & n,
    const int & kl,
    const int & ku,
    const int & nrhs,
    const double * ab,
    const int & ldab,
    const double * afb,
    const int & ldafb,
    const int * ipiv,
    const double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dgbsv(
    const int & n,
    const int & kl,
    const int & ku,
    const int & nrhs,
    double * ab,
    const int & ldab,
    int * ipiv,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dgbsvx(
    const char & fact,
    const char & trans,
    const int & n,
    const int & kl,
    const int & ku,
    const int & nrhs,
    double * ab,
    const int & ldab,
    double * afb,
    const int & ldafb,
    int * ipiv,
    char & equed,
    double * r,
    double * c,
    double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dgbtrf(
    const int & m,
    const int & n,
    const int & kl,
    const int & ku,
    double * ab,
    const int & ldab,
    int * ipiv,
    int & info
);

void MCLA_API f77_dgbtrs(
    const char & trans,
    const int & n,
    const int & kl,
    const int & ku,
    const int & nrhs,
    const double * ab,
    const int & ldab,
    const int * ipiv,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dgebak(
    const char & job,
    const char & side,
    const int & n,
    const int & ilo,
    const int & ihi,
    const double * scale,
    const int & m,
    double * v,
    const int & ldv,
    int & info
);

void MCLA_API f77_dgebal(
    const char & job,
    const int & n,
    double * a,
    const int & lda,
    int & ilo,
    int & ihi,
    double * scale,
    int & info
);

void MCLA_API f77_dgebrd(
    const int & m,
    const int & n,
    double * a,
    const int & lda,
    double * d,
    double * e,
    double * tauq,
    double * taup,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dgecon(
    const char & norm,
    const int & n,
    const double * a,
    const int & lda,
    const double & anorm,
    double & rcond,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dgeequ(
    const int & m,
    const int & n,
    const double * a,
    const int & lda,
    double * r,
    double * c,
    double & rowcnd,
    double & colcnd,
    double & amax,
    int & info
);

void MCLA_API f77_dgees(
    const char & jobvs,
    const char & sort,
    int (* select)(...),
    const int & n,
    double * a,
    const int & lda,
    int & sdim,
    double * wr,
    double * wi,
    double * vs,
    const int & ldvs,
    double * work,
    const int & lwork,
    int * bwork,
    int & info
);

void MCLA_API f77_dgeesx(
    const char & jobvs,
    const char & sort,
    int (* select)(...),
    const char & sense,
    const int & n,
    double * a,
    const int & lda,
    int & sdim,
    double * wr,
    double * wi,
    double * vs,
    const int & ldvs,
    double & rconde,
    double & rcondv,
    double * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int * bwork,
    int & info
);

void MCLA_API f77_dgeev(
    const char & jobvl,
    const char & jobvr,
    const int & n,
    double * a,
    const int & lda,
    double * wr,
    double * wi,
    double * vl,
    const int & ldvl,
    double * vr,
    const int & ldvr,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dgeevx(
    const char & balanc,
    const char & jobvl,
    const char & jobvr,
    const char & sense,
    const int & n,
    double * a,
    const int & lda,
    double * wr,
    double * wi,
    double * vl,
    const int & ldvl,
    double * vr,
    const int & ldvr,
    int & ilo,
    int & ihi,
    double * scale,
    double & abnrm,
    double * rconde,
    double * rcondv,
    double * work,
    const int & lwork,
    int * iwork,
    int & info
);

void MCLA_API f77_dgehrd(
    const int & n,
    const int & ilo,
    const int & ihi,
    double * a,
    const int & lda,
    double * tau,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dgelqf(
    const int & m,
    const int & n,
    double * a,
    const int & lda,
    double * tau,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dgels(
    const char & trans,
    const int & m,
    const int & n,
    const int & nrhs,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dgelsd(
    const int & m,
    const int & n,
    const int & nrhs,
    const double * a,
    const int & lda,
    double * b,
    const int & ldb,
    double * s,
    const double & rcond,
    int & rank,
    double * work,
    const int & lwork,
    int * iwork,
    int & info
);

void MCLA_API f77_dgelss(
    const int & m,
    const int & n,
    const int & nrhs,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    double * s,
    const double & rcond,
    int & rank,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dgelsy(
    const int & m,
    const int & n,
    const int & nrhs,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    int * jpvt,
    const double & rcond,
    int & rank,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dgeqlf(
    const int & m,
    const int & n,
    double * a,
    const int & lda,
    double * tau,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dgeqp3(
    const int & m,
    const int & n,
    double * a,
    const int & lda,
    int * jpvt,
    double * tau,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dgeqrf(
    const int & m,
    const int & n,
    double * a,
    const int & lda,
    double * tau,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dgerfs(
    const char & trans,
    const int & n,
    const int & nrhs,
    const double * a,
    const int & lda,
    const double * af,
    const int & ldaf,
    const int * ipiv,
    const double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dgerqf(
    const int & m,
    const int & n,
    double * a,
    const int & lda,
    double * tau,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dgesdd(
    const char & jobz,
    const int & m,
    const int & n,
    double * a,
    const int & lda,
    double * s,
    double * u,
    const int & ldu,
    double * vt,
    const int & ldvt,
    double * work,
    const int & lwork,
    int * iwork,
    int & info
);

void MCLA_API f77_dgesv(
    const int & n,
    const int & nrhs,
    double * a,
    const int & lda,
    int * ipiv,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dgesvd(
    const char & jobu,
    const char & jobvt,
    const int & m,
    const int & n,
    double * a,
    const int & lda,
    double * s,
    double * u,
    const int & ldu,
    double * vt,
    const int & ldvt,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dgesvx(
    const char & fact,
    const char & trans,
    const int & n,
    const int & nrhs,
    double * a,
    const int & lda,
    double * af,
    const int & ldaf,
    int * ipiv,
    char & equed,
    double * r,
    double * c,
    double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dgetrf(
    const int & m,
    const int & n,
    double * a,
    const int & lda,
    int * ipiv,
    int & info
);

void MCLA_API f77_dgetri(
    const int & n,
    double * a,
    const int & lda,
    const int * ipiv,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dgetrs(
    const char & trans,
    const int & n,
    const int & nrhs,
    const double * a,
    const int & lda,
    const int * ipiv,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dggbak(
    const char & job,
    const char & side,
    const int & n,
    const int & ilo,
    const int & ihi,
    const double * lscale,
    const double * rscale,
    const int & m,
    double * v,
    const int & ldv,
    int & info
);

void MCLA_API f77_dggbal(
    const char & job,
    const int & n,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    int & ilo,
    int & ihi,
    double * lscale,
    double * rscale,
    double * work,
    int & info
);

void MCLA_API f77_dgges(
    const char & jobvsl,
    const char & jobvsr,
    const char & sort,
    int (* delctg)(...),
    const int & n,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    int & sdim,
    double * alphar,
    double * alphai,
    double * beta,
    double * vsl,
    const int & ldvsl,
    double * vsr,
    const int & ldvsr,
    double * work,
    const int & lwork,
    int * bwork,
    int & info
);

void MCLA_API f77_dggesx(
    const char & jobvsl,
    const char & jobvsr,
    const char & sort,
    int (* delctg)(...),
    const char & sense,
    const int & n,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    int & sdim,
    double * alphar,
    double * alphai,
    double * beta,
    double * vsl,
    const int & ldvsl,
    double * vsr,
    const int & ldvsr,
    double * rconde,
    double * rcondv,
    double * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int * bwork,
    int & info
);

void MCLA_API f77_dggev(
    const char & jobvl,
    const char & jobvr,
    const int & n,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    double * alphar,
    double * alphai,
    double * beta,
    double * vl,
    const int & ldvl,
    double * vr,
    const int & ldvr,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dggevx(
    const char & balanc,
    const char & jobvl,
    const char & jobvr,
    const char & sense,
    const int & n,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    double * alphar,
    double * alphai,
    double * beta,
    double * vl,
    const int & ldvl,
    double * vr,
    const int & ldvr,
    int & ilo,
    int & ihi,
    double * lscale,
    double * rscale,
    double & abnrm,
    double & bbnrm,
    double * rconde,
    double * rcondv,
    double * work,
    const int & lwork,
    int * iwork,
    int * bwork,
    int & info
);

void MCLA_API f77_dggglm(
    const int & n,
    const int & m,
    const int & p,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    double * d,
    double * x,
    double * y,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dgghrd(
    const char & compq,
    const char & compz,
    const int & n,
    const int & ilo,
    const int & ihi,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    double * q,
    const int & ldq,
    double * z,
    const int & ldz,
    int & info
);

void MCLA_API f77_dgglse(
    const int & m,
    const int & n,
    const int & p,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    double * c,
    double * d,
    double * x,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dggqrf(
    const int & n,
    const int & m,
    const int & p,
    double * a,
    const int & lda,
    double * taua,
    double * b,
    const int & ldb,
    double * taub,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dggrqf(
    const int & m,
    const int & p,
    const int & n,
    double * a,
    const int & lda,
    double * taua,
    double * b,
    const int & ldb,
    double * taub,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dggsvd(
    const char & jobu,
    const char & jobv,
    const char & jobq,
    const int & m,
    const int & n,
    const int & p,
    int & k,
    int & l,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    double * alpha,
    double * beta,
    double * u,
    const int & ldu,
    double * v,
    const int & ldv,
    double * q,
    const int & ldq,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dggsvp(
    const char & jobu,
    const char & jobv,
    const char & jobq,
    const int & m,
    const int & p,
    const int & n,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    const double & tola,
    const double & tolb,
    int & k,
    int & l,
    double * u,
    const int & ldu,
    double * v,
    const int & ldv,
    double * q,
    const int & ldq,
    int * iwork,
    double * tau,
    double * work,
    int & info
);

void MCLA_API f77_dgtcon(
    const char & norm,
    const int & n,
    const double * dl,
    const double * d,
    const double * du,
    const double * du2,
    const int * ipiv,
    const double & anorm,
    double & rcond,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dgtrfs(
    const char & trans,
    const int & n,
    const int & nrhs,
    const double * dl,
    const double * d,
    const double * du,
    const double * dlf,
    const double * df,
    const double * duf,
    const double * du2,
    const int * ipiv,
    const double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dgtsv(
    const int & n,
    const int & nrhs,
    double * dl,
    double * d,
    double * du,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dgtsvx(
    const char & fact,
    const char & trans,
    const int & n,
    const int & nrhs,
    const double * dl,
    const double * d,
    const double * du,
    double * dlf,
    double * df,
    double * duf,
    double * du2,
    int * ipiv,
    const double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dgttrf(
    const int & n,
    double * dl,
    double * d,
    double * du,
    double * du2,
    int * ipiv,
    int & info
);

void MCLA_API f77_dgttrs(
    const char & trans,
    const int & n,
    const int & nrhs,
    const double * dl,
    const double * d,
    const double * du,
    const double * du2,
    const int * ipiv,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dhgeqz(
    const char & job,
    const char & compq,
    const char & compz,
    const int & n,
    const int & ilo,
    const int & ihi,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    double * alphar,
    double * alphai,
    double * beta,
    double * q,
    const int & ldq,
    double * z,
    const int & ldz,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dhsein(
    const char & side,
    const char & eigsrc,
    const char & initv,
    int * select,
    const int & n,
    const double * h,
    const int & ldh,
    double * wr,
    const double * wi,
    double * vl,
    const int & ldvl,
    double * vr,
    const int & ldvr,
    const int & mm,
    int & m,
    double * work,
    int * ifaill,
    int * ifailr,
    int & info
);

void MCLA_API f77_dhseqr(
    const char & job,
    const char & compz,
    const int & n,
    const int & ilo,
    const int & ihi,
    double * h,
    const int & ldh,
    double * wr,
    double * wi,
    double * z,
    const int & ldz,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dopgtr(
    const char & uplo,
    const int & n,
    const double * ap,
    const double * tau,
    double * q,
    const int & ldq,
    double * work,
    int & info
);

void MCLA_API f77_dopmtr(
    const char & side,
    const char & uplo,
    const char & trans,
    const int & m,
    const int & n,
    const double * ap,
    const double * tau,
    double * c,
    const int & ldc,
    double * work,
    int & info
);

void MCLA_API f77_dorgbr(
    const char & vect,
    const int & m,
    const int & n,
    const int & k,
    double * a,
    const int & lda,
    const double * tau,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dorghr(
    const int & n,
    const int & ilo,
    const int & ihi,
    double * a,
    const int & lda,
    const double * tau,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dorglq(
    const int & m,
    const int & n,
    const int & k,
    double * a,
    const int & lda,
    const double * tau,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dorgql(
    const int & m,
    const int & n,
    const int & k,
    double * a,
    const int & lda,
    const double * tau,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dorgqr(
    const int & m,
    const int & n,
    const int & k,
    double * a,
    const int & lda,
    const double * tau,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dorgrq(
    const int & m,
    const int & n,
    const int & k,
    double * a,
    const int & lda,
    const double * tau,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dorgtr(
    const char & uplo,
    const int & n,
    double * a,
    const int & lda,
    const double * tau,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dormbr(
    const char & vect,
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const double * a,
    const int & lda,
    const double * tau,
    double * c,
    const int & ldc,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dormhr(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & ilo,
    const int & ihi,
    const double * a,
    const int & lda,
    const double * tau,
    double * c,
    const int & ldc,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dormlq(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const double * a,
    const int & lda,
    const double * tau,
    double * c,
    const int & ldc,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dormql(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const double * a,
    const int & lda,
    const double * tau,
    double * c,
    const int & ldc,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dormqr(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const double * a,
    const int & lda,
    const double * tau,
    double * c,
    const int & ldc,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dormrq(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const double * a,
    const int & lda,
    const double * tau,
    double * c,
    const int & ldc,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dormrz(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const int & l,
    const double * a,
    const int & lda,
    const double * tau,
    double * c,
    const int & ldc,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dormtr(
    const char & side,
    const char & uplo,
    const char & trans,
    const int & m,
    const int & n,
    const double * a,
    const int & lda,
    const double * tau,
    double * c,
    const int & ldc,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dpbcon(
    const char & uplo,
    const int & n,
    const int & kd,
    const double * ab,
    const int & ldab,
    const double & anorm,
    double & rcond,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dpbequ(
    const char & uplo,
    const int & n,
    const int & kd,
    const double * ab,
    const int & ldab,
    double * s,
    double & scond,
    double & amax,
    int & info
);

void MCLA_API f77_dpbrfs(
    const char & uplo,
    const int & n,
    const int & kd,
    const int & nrhs,
    const double * ab,
    const int & ldab,
    const double * afb,
    const int & ldafb,
    const double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dpbstf(
    const char & uplo,
    const int & n,
    const int & kd,
    double * ab,
    const int & ldab,
    int & info
);

void MCLA_API f77_dpbsv(
    const char & uplo,
    const int & n,
    const int & kd,
    const int & nrhs,
    double * ab,
    const int & ldab,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dpbsvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & kd,
    const int & nrhs,
    double * ab,
    const int & ldab,
    double * afb,
    const int & ldafb,
    char & equed,
    double * s,
    double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dpbtrf(
    const char & uplo,
    const int & n,
    const int & kd,
    double * ab,
    const int & ldab,
    int & info
);

void MCLA_API f77_dpbtrs(
    const char & uplo,
    const int & n,
    const int & kd,
    const int & nrhs,
    const double * ab,
    const int & ldab,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dpocon(
    const char & uplo,
    const int & n,
    const double * a,
    const int & lda,
    const double & anorm,
    double & rcond,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dpoequ(
    const int & n,
    const double * a,
    const int & lda,
    double * s,
    double & scond,
    double & amax,
    int & info
);

void MCLA_API f77_dporfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const double * a,
    const int & lda,
    const double * af,
    const int & ldaf,
    const double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dposv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dposvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    double * a,
    const int & lda,
    double * af,
    const int & ldaf,
    char & equed,
    double * s,
    double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dpotrf(
    const char & uplo,
    const int & n,
    double * a,
    const int & lda,
    int & info
);

void MCLA_API f77_dpotri(
    const char & uplo,
    const int & n,
    double * a,
    const int & lda,
    int & info
);

void MCLA_API f77_dpotrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const double * a,
    const int & lda,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dppcon(
    const char & uplo,
    const int & n,
    const double * ap,
    const double & anorm,
    double & rcond,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dppequ(
    const char & uplo,
    const int & n,
    const double * ap,
    double * s,
    double & scond,
    double & amax,
    int & info
);

void MCLA_API f77_dpprfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const double * ap,
    const double * afp,
    const double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dppsv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    double * ap,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dppsvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    double * ap,
    double * afp,
    char & equed,
    double * s,
    double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dpptrf(
    const char & uplo,
    const int & n,
    double * ap,
    int & info
);

void MCLA_API f77_dpptri(
    const char & uplo,
    const int & n,
    double * ap,
    int & info
);

void MCLA_API f77_dpptrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const double * ap,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dptcon(
    const int & n,
    const double * d,
    const double * e,
    const double & anorm,
    double & rcond,
    double * work,
    int & info
);

void MCLA_API f77_dpteqr(
    const char & compz,
    const int & n,
    double * d,
    double * e,
    double * z,
    const int & ldz,
    double * work,
    int & info
);

void MCLA_API f77_dptrfs(
    const int & n,
    const int & nrhs,
    const double * d,
    const double * e,
    const double * df,
    const double * ef,
    const double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    double * work,
    int & info
);

void MCLA_API f77_dptsv(
    const int & n,
    const int & nrhs,
    double * d,
    double * e,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dptsvx(
    const char & fact,
    const int & n,
    const int & nrhs,
    const double * d,
    const double * e,
    double * df,
    double * ef,
    const double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    double * work,
    int & info
);

void MCLA_API f77_dpttrf(
    const int & n,
    double * d,
    double * e,
    int & info
);

void MCLA_API f77_dpttrs(
    const int & n,
    const int & nrhs,
    const double * d,
    const double * e,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dsbev(
    const char & jobz,
    const char & uplo,
    const int & n,
    const int & kd,
    double * ab,
    const int & ldab,
    double * w,
    double * z,
    const int & ldz,
    double * work,
    int & info
);

void MCLA_API f77_dsbevd(
    const char & jobz,
    const char & uplo,
    const int & n,
    const int & kd,
    double * ab,
    const int & ldab,
    double * w,
    double * z,
    const int & ldz,
    double * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_dsbevx(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    const int & kd,
    double * ab,
    const int & ldab,
    double * q,
    const int & ldq,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    double * z,
    const int & ldz,
    double * work,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_dsbgst(
    const char & vect,
    const char & uplo,
    const int & n,
    const int & ka,
    const int & kb,
    double * ab,
    const int & ldab,
    const double * bb,
    const int & ldbb,
    double * x,
    const int & ldx,
    double * work,
    int & info
);

void MCLA_API f77_dsbgv(
    const char & jobz,
    const char & uplo,
    const int & n,
    const int & ka,
    const int & kb,
    double * ab,
    const int & ldab,
    double * bb,
    const int & ldbb,
    double * w,
    double * z,
    const int & ldz,
    double * work,
    int & info
);

void MCLA_API f77_dsbgvd(
    const char & jobz,
    const char & uplo,
    const int & n,
    const int & ka,
    const int & kb,
    double * ab,
    const int & ldab,
    double * bb,
    const int & ldbb,
    double * w,
    double * z,
    const int & ldz,
    double * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_dsbgvx(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    const int & ka,
    const int & kb,
    double * ab,
    const int & ldab,
    double * bb,
    const int & ldbb,
    double * q,
    const int & ldq,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    double * z,
    const int & ldz,
    double * work,
    int * iwork,
    const int * ifail,
    int & info
);

void MCLA_API f77_dsbtrd(
    const char & vect,
    const char & uplo,
    const int & n,
    const int & kd,
    double * ab,
    const int & ldab,
    double * d,
    double * e,
    double * q,
    const int & ldq,
    double * work,
    int & info
);

void MCLA_API f77_dspcon(
    const char & uplo,
    const int & n,
    const double * ap,
    const int * ipiv,
    const double & anorm,
    double & rcond,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dspev(
    const char & jobz,
    const char & uplo,
    const int & n,
    double * ap,
    double * w,
    double * z,
    const int & ldz,
    double * work,
    int & info
);

void MCLA_API f77_dspevd(
    const char & jobz,
    const char & uplo,
    const int & n,
    double * ap,
    double * w,
    double * z,
    const int & ldz,
    double * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_dspevx(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    double * ap,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    double * z,
    const int & ldz,
    double * work,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_dspgst(
    const int & itype,
    const char & uplo,
    const int & n,
    double * ap,
    const double * bp,
    int & info
);

void MCLA_API f77_dspgv(
    const int & itype,
    const char & jobz,
    const char & uplo,
    const int & n,
    double * ap,
    double * bp,
    double * w,
    double * z,
    const int & ldz,
    double * work,
    int & info
);

void MCLA_API f77_dspgvd(
    const int & itype,
    const char & jobz,
    const char & uplo,
    const int & n,
    double * ap,
    double * bp,
    double * w,
    double * z,
    const int & ldz,
    double * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_dspgvx(
    const int & itype,
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    double * ap,
    double * bp,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    double * z,
    const int & ldz,
    double * work,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_dsprfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const double * ap,
    const double * afp,
    const int * ipiv,
    const double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dspsv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    double * ap,
    int * ipiv,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dspsvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    const double * ap,
    double * afp,
    int * ipiv,
    const double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dsptrd(
    const char & uplo,
    const int & n,
    double * ap,
    double * d,
    double * e,
    double * tau,
    int & info
);

void MCLA_API f77_dsptrf(
    const char & uplo,
    const int & n,
    double * ap,
    int * ipiv,
    int & info
);

void MCLA_API f77_dsptri(
    const char & uplo,
    const int & n,
    double * ap,
    const int * ipiv,
    double * work,
    int & info
);

void MCLA_API f77_dsptrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const double * ap,
    const int * ipiv,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dstebz(
    const char & range,
    const char & order,
    const int & n,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    const double * d,
    const double * e,
    int & m,
    int & nsplit,
    double * w,
    int * iblock,
    int * isplit,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dstedc(
    const char & compz,
    const int & n,
    double * d,
    double * e,
    double * z,
    const int & ldz,
    double * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_dstegr(
    const char & jobz,
    const char & range,
    const int & n,
    double * d,
    double * e,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    double * z,
    const int & ldz,
    int * isuppz,
    double * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_dstein(
    const int & n,
    const double * d,
    const double * e,
    const int & m,
    const double * w,
    const int * iblock,
    const int * isplit,
    double * z,
    const int & ldz,
    double * work,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_dsteqr(
    const char & compz,
    const int & n,
    double * d,
    double * e,
    double * z,
    const int & ldz,
    double * work,
    int & info
);

void MCLA_API f77_dsterf(
    const int & n,
    double * d,
    double * e,
    int & info
);

void MCLA_API f77_dstev(
    const char & jobz,
    const int & n,
    double * d,
    double * e,
    double * z,
    const int & ldz,
    double * work,
    int & info
);

void MCLA_API f77_dstevd(
    const char & jobz,
    const int & n,
    double * d,
    double * e,
    double * z,
    const int & ldz,
    double * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_dstevr(
    const char & jobz,
    const char & range,
    const int & n,
    double * d,
    double * e,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    double * z,
    const int & ldz,
    int * isuppz,
    double * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_dstevx(
    const char & jobz,
    const char & range,
    const int & n,
    double * d,
    double * e,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    double * z,
    const int & ldz,
    double * work,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_dsycon(
    const char & uplo,
    const int & n,
    const double * a,
    const int & lda,
    const int * ipiv,
    const double & anorm,
    double & rcond,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dsyev(
    const char & jobz,
    const char & uplo,
    const int & n,
    double * a,
    const int & lda,
    double * w,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dsyevd(
    const char & jobz,
    const char & uplo,
    const int & n,
    double * a,
    const int & lda,
    double * w,
    double * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_dsyevr(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    double * a,
    const int & lda,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    double * z,
    const int & ldz,
    int * isuppz,
    double * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_dsyevx(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    double * a,
    const int & lda,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    double * z,
    const int & ldz,
    double * work,
    const int & lwork,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_dsygst(
    const int & itype,
    const char & uplo,
    const int & n,
    double * a,
    const int & lda,
    const double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dsygv(
    const int & itype,
    const char & jobz,
    const char & uplo,
    const int & n,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    double * w,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dsygvd(
    const int & itype,
    const char & jobz,
    const char & uplo,
    const int & n,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    double * w,
    double * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_dsygvx(
    const int & itype,
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    double * z,
    const int & ldz,
    double * work,
    const int & lwork,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_dsyrfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const double * a,
    const int & lda,
    const double * af,
    const int & ldaf,
    const int * ipiv,
    const double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dsysv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    double * a,
    const int & lda,
    int * ipiv,
    double * b,
    const int & ldb,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dsysvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    const double * a,
    const int & lda,
    double * af,
    const int & ldaf,
    int * ipiv,
    const double * b,
    const int & ldb,
    double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    double * work,
    const int & lwork,
    int * iwork,
    int & info
);

void MCLA_API f77_dsytrd(
    const char & uplo,
    const int & n,
    double * a,
    const int & lda,
    double * d,
    double * e,
    double * tau,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dsytrf(
    const char & uplo,
    const int & n,
    double * a,
    const int & lda,
    int * ipiv,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dsytri(
    const char & uplo,
    const int & n,
    double * a,
    const int & lda,
    const int * ipiv,
    double * work,
    int & info
);

void MCLA_API f77_dsytrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const double * a,
    const int & lda,
    const int * ipiv,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dtbcon(
    const char & norm,
    const char & uplo,
    const char & diag,
    const int & n,
    const int & kd,
    const double * ab,
    const int & ldab,
    double & rcond,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dtbrfs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & kd,
    const int & nrhs,
    const double * ab,
    const int & ldab,
    const double * b,
    const int & ldb,
    const double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dtbtrs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & kd,
    const int & nrhs,
    const double * ab,
    const int & ldab,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dtgevc(
    const char & side,
    const char & howmny,
    const int * select,
    const int & n,
    const double * a,
    const int & lda,
    const double * b,
    const int & ldb,
    double * vl,
    const int & ldvl,
    double * vr,
    const int & ldvr,
    const int & mm,
    int & m,
    double * work,
    int & info
);

void MCLA_API f77_dtgexc(
    const int & wantq,
    const int & wantz,
    const int & n,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    double * q,
    const int & ldq,
    double * z,
    const int & ldz,
    int & ifst,
    int & ilst,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_dtgsen(
    const int & ijob,
    const int & wantq,
    const int & wantz,
    const int * select,
    const int & n,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    double * alphar,
    double * alphai,
    double * beta,
    double * q,
    const int & ldq,
    double * z,
    const int & ldz,
    int & m,
    double & pl,
    double & pr,
    double * dif,
    double * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_dtgsja(
    const char & jobu,
    const char & jobv,
    const char & jobq,
    const int & m,
    const int & p,
    const int & n,
    const int & k,
    const int & l,
    double * a,
    const int & lda,
    double * b,
    const int & ldb,
    const double & tola,
    const double & tolb,
    double * alpha,
    double * beta,
    double * u,
    const int & ldu,
    double * v,
    const int & ldv,
    double * q,
    const int & ldq,
    double * work,
    int & ncycle,
    int & info
);

void MCLA_API f77_dtgsna(
    const char & job,
    const char & howmny,
    const int * select,
    const int & n,
    const double * a,
    const int & lda,
    const double * b,
    const int & ldb,
    const double * vl,
    const int & ldvl,
    const double * vr,
    const int & ldvr,
    double * s,
    double * dif,
    const int & mm,
    int & m,
    double * work,
    const int & lwork,
    int * iwork,
    int & info
);

void MCLA_API f77_dtgsyl(
    const char & trans,
    const int & ijob,
    const int & m,
    const int & n,
    const double * a,
    const int & lda,
    const double * b,
    const int & ldb,
    double * c,
    const int & ldc,
    const double * d,
    const int & ldd,
    const double * e,
    const int & lde,
    double * f,
    const int & ldf,
    double & scale,
    double & dif,
    double * work,
    const int & lwork,
    int * iwork,
    int & info
);

void MCLA_API f77_dtpcon(
    const char & norm,
    const char & uplo,
    const char & diag,
    const int & n,
    const double * ap,
    double & rcond,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dtprfs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & nrhs,
    const double * ap,
    const double * b,
    const int & ldb,
    const double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dtptri(
    const char & uplo,
    const char & diag,
    const int & n,
    double * ap,
    int & info
);

void MCLA_API f77_dtptrs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & nrhs,
    const double * ap,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dtrcon(
    const char & norm,
    const char & uplo,
    const char & diag,
    const int & n,
    const double * a,
    const int & lda,
    double & rcond,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dtrevc(
    const char & side,
    const char & howmny,
    int * select,
    const int & n,
    const double * t,
    const int & ldt,
    double * vl,
    const int & ldvl,
    double * vr,
    const int & ldvr,
    const int & mm,
    int & m,
    double * work,
    int & info
);

void MCLA_API f77_dtrexc(
    const char & compq,
    const int & n,
    double * t,
    const int & ldt,
    double * q,
    const int & ldq,
    int & ifst,
    int & ilst,
    double * work,
    int & info
);

void MCLA_API f77_dtrrfs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & nrhs,
    const double * a,
    const int & lda,
    const double * b,
    const int & ldb,
    const double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    double * work,
    int * iwork,
    int & info
);

void MCLA_API f77_dtrsen(
    const char & job,
    const char & compq,
    const int * select,
    const int & n,
    double * t,
    const int & ldt,
    double * q,
    const int & ldq,
    double * wr,
    double * wi,
    int & m,
    double & s,
    double & sep,
    double * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_dtrsna(
    const char & job,
    const char & howmny,
    const int * select,
    const int & n,
    const double * t,
    const int & ldt,
    const double * vl,
    const int & ldvl,
    const double * vr,
    const int & ldvr,
    double * s,
    double * sep,
    const int & mm,
    int & m,
    double * work,
    const int & ldwork,
    int * iwork,
    int & info
);

void MCLA_API f77_dtrsyl(
    const char & trana,
    const char & tranb,
    const int & isgn,
    const int & m,
    const int & n,
    const double * a,
    const int & lda,
    const double * b,
    const int & ldb,
    double * c,
    const int & ldc,
    double & scale,
    int & info
);

void MCLA_API f77_dtrtri(
    const char & uplo,
    const char & diag,
    const int & n,
    double * a,
    const int & lda,
    int & info
);

void MCLA_API f77_dtrtrs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & nrhs,
    const double * a,
    const int & lda,
    double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_dtzrzf(
    const int & m,
    const int & n,
    double * a,
    const int & lda,
    double * tau,
    double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sbdsdc(
    const char & uplo,
    const char & compq,
    const int & n,
    float * d,
    float * e,
    float * u,
    const int & ldu,
    float * vt,
    const int & ldvt,
    float * q,
    int * iq,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_sbdsqr(
    const char & uplo,
    const int & n,
    const int & ncvt,
    const int & nru,
    const int & ncc,
    float * d,
    float * e,
    float * vt,
    const int & ldvt,
    float * u,
    const int & ldu,
    float * c,
    const int & ldc,
    float * work,
    int & info
);

void MCLA_API f77_sdisna(
    const char & job,
    const int & m,
    const int & n,
    const float * d,
    float * sep,
    int & info
);

void MCLA_API f77_sgbbrd(
    const char & vect,
    const int & m,
    const int & n,
    const int & ncc,
    const int & kl,
    const int & ku,
    float * ab,
    const int & ldab,
    float * d,
    float * e,
    float * q,
    const int & ldq,
    float * pt,
    const int & ldpt,
    float * c,
    const int & ldc,
    float * work,
    int & info
);

void MCLA_API f77_sgbcon(
    const char & norm,
    const int & n,
    const int & kl,
    const int & ku,
    const float * ab,
    const int & ldab,
    const int * ipiv,
    const float & anorm,
    float & rcond,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_sgbequ(
    const int & m,
    const int & n,
    const int & kl,
    const int & ku,
    const float * ab,
    const int & ldab,
    float * r,
    float * c,
    float & rowcnd,
    float & colcnd,
    float & amax,
    int & info
);

void MCLA_API f77_sgbrfs(
    const char & trans,
    const int & n,
    const int & kl,
    const int & ku,
    const int & nrhs,
    const float * ab,
    const int & ldab,
    const float * afb,
    const int & ldafb,
    const int * ipiv,
    const float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_sgbsv(
    const int & n,
    const int & kl,
    const int & ku,
    const int & nrhs,
    float * ab,
    const int & ldab,
    int * ipiv,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_sgbsvx(
    const char & fact,
    const char & trans,
    const int & n,
    const int & kl,
    const int & ku,
    const int & nrhs,
    float * ab,
    const int & ldab,
    float * afb,
    const int & ldafb,
    int * ipiv,
    char & equed,
    float * r,
    float * c,
    float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_sgbtrf(
    const int & m,
    const int & n,
    const int & kl,
    const int & ku,
    float * ab,
    const int & ldab,
    int * ipiv,
    int & info
);

void MCLA_API f77_sgbtrs(
    const char & trans,
    const int & n,
    const int & kl,
    const int & ku,
    const int & nrhs,
    const float * ab,
    const int & ldab,
    const int * ipiv,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_sgebak(
    const char & job,
    const char & side,
    const int & n,
    const int & ilo,
    const int & ihi,
    const float * scale,
    const int & m,
    float * v,
    const int & ldv,
    int & info
);

void MCLA_API f77_sgebal(
    const char & job,
    const int & n,
    float * a,
    const int & lda,
    int & ilo,
    int & ihi,
    float * scale,
    int & info
);

void MCLA_API f77_sgebrd(
    const int & m,
    const int & n,
    float * a,
    const int & lda,
    float * d,
    float * e,
    float * tauq,
    float * taup,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sgecon(
    const char & norm,
    const int & n,
    const float * a,
    const int & lda,
    const float & anorm,
    float & rcond,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_sgeequ(
    const int & m,
    const int & n,
    const float * a,
    const int & lda,
    float * r,
    float * c,
    float & rowcnd,
    float & colcnd,
    float & amax,
    int & info
);

void MCLA_API f77_sgees(
    const char & jobvs,
    const char & sort,
    int (* select)(...),
    const int & n,
    float * a,
    const int & lda,
    int & sdim,
    float * wr,
    float * wi,
    float * vs,
    const int & ldvs,
    float * work,
    const int & lwork,
    int * bwork,
    int & info
);

void MCLA_API f77_sgeesx(
    const char & jobvs,
    const char & sort,
    int (* select)(...),
    const char & sense,
    const int & n,
    float * a,
    const int & lda,
    int & sdim,
    float * wr,
    float * wi,
    float * vs,
    const int & ldvs,
    float & rconde,
    float & rcondv,
    float * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int * bwork,
    int & info
);

void MCLA_API f77_sgeev(
    const char & jobvl,
    const char & jobvr,
    const int & n,
    float * a,
    const int & lda,
    float * wr,
    float * wi,
    float * vl,
    const int & ldvl,
    float * vr,
    const int & ldvr,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sgeevx(
    const char & balanc,
    const char & jobvl,
    const char & jobvr,
    const char & sense,
    const int & n,
    float * a,
    const int & lda,
    float * wr,
    float * wi,
    float * vl,
    const int & ldvl,
    float * vr,
    const int & ldvr,
    int & ilo,
    int & ihi,
    float * scale,
    float & abnrm,
    float * rconde,
    float * rcondv,
    float * work,
    const int & lwork,
    int * iwork,
    int & info
);

void MCLA_API f77_sgehrd(
    const int & n,
    const int & ilo,
    const int & ihi,
    float * a,
    const int & lda,
    float * tau,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sgelqf(
    const int & m,
    const int & n,
    float * a,
    const int & lda,
    float * tau,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sgels(
    const char & trans,
    const int & m,
    const int & n,
    const int & nrhs,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sgelsd(
    const int & m,
    const int & n,
    const int & nrhs,
    const float * a,
    const int & lda,
    float * b,
    const int & ldb,
    float * s,
    const float & rcond,
    int & rank,
    float * work,
    const int & lwork,
    int * iwork,
    int & info
);

void MCLA_API f77_sgelss(
    const int & m,
    const int & n,
    const int & nrhs,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    float * s,
    const float & rcond,
    int & rank,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sgelsy(
    const int & m,
    const int & n,
    const int & nrhs,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    int * jpvt,
    const float & rcond,
    int & rank,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sgeqlf(
    const int & m,
    const int & n,
    float * a,
    const int & lda,
    float * tau,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sgeqp3(
    const int & m,
    const int & n,
    float * a,
    const int & lda,
    int * jpvt,
    float * tau,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sgeqrf(
    const int & m,
    const int & n,
    float * a,
    const int & lda,
    float * tau,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sgerfs(
    const char & trans,
    const int & n,
    const int & nrhs,
    const float * a,
    const int & lda,
    const float * af,
    const int & ldaf,
    const int * ipiv,
    const float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_sgerqf(
    const int & m,
    const int & n,
    float * a,
    const int & lda,
    float * tau,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sgesdd(
    const char & jobz,
    const int & m,
    const int & n,
    float * a,
    const int & lda,
    float * s,
    float * u,
    const int & ldu,
    float * vt,
    const int & ldvt,
    float * work,
    const int & lwork,
    int * iwork,
    int & info
);

void MCLA_API f77_sgesv(
    const int & n,
    const int & nrhs,
    float * a,
    const int & lda,
    int * ipiv,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_sgesvd(
    const char & jobu,
    const char & jobvt,
    const int & m,
    const int & n,
    float * a,
    const int & lda,
    float * s,
    float * u,
    const int & ldu,
    float * vt,
    const int & ldvt,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sgesvx(
    const char & fact,
    const char & trans,
    const int & n,
    const int & nrhs,
    float * a,
    const int & lda,
    float * af,
    const int & ldaf,
    int * ipiv,
    char & equed,
    float * r,
    float * c,
    float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_sgetrf(
    const int & m,
    const int & n,
    float * a,
    const int & lda,
    int * ipiv,
    int & info
);

void MCLA_API f77_sgetri(
    const int & n,
    float * a,
    const int & lda,
    const int * ipiv,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sgetrs(
    const char & trans,
    const int & n,
    const int & nrhs,
    const float * a,
    const int & lda,
    const int * ipiv,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_sggbak(
    const char & job,
    const char & side,
    const int & n,
    const int & ilo,
    const int & ihi,
    const float * lscale,
    const float * rscale,
    const int & m,
    float * v,
    const int & ldv,
    int & info
);

void MCLA_API f77_sggbal(
    const char & job,
    const int & n,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    int & ilo,
    int & ihi,
    float * lscale,
    float * rscale,
    float * work,
    int & info
);

void MCLA_API f77_sgges(
    const char & jobvsl,
    const char & jobvsr,
    const char & sort,
    int (* selctg)(...),
    const int & n,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    int & sdim,
    float * alphar,
    float * alphai,
    float * beta,
    float * vsl,
    const int & ldvsl,
    float * vsr,
    const int & ldvsr,
    float * work,
    const int & lwork,
    int * bwork,
    int & info
);

void MCLA_API f77_sggesx(
    const char & jobvsl,
    const char & jobvsr,
    const char & sort,
    int (* selctg)(...),
    const char & sense,
    const int & n,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    int & sdim,
    float * alphar,
    float * alphai,
    float * beta,
    float * vsl,
    const int & ldvsl,
    float * vsr,
    const int & ldvsr,
    float * rconde,
    float * rcondv,
    float * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int * bwork,
    int & info
);

void MCLA_API f77_sggev(
    const char & jobvl,
    const char & jobvr,
    const int & n,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    float * alphar,
    float * alphai,
    float * beta,
    float * vl,
    const int & ldvl,
    float * vr,
    const int & ldvr,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sggevx(
    const char & balanc,
    const char & jobvl,
    const char & jobvr,
    const char & sense,
    const int & n,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    float * alphar,
    float * alphai,
    float * beta,
    float * vl,
    const int & ldvl,
    float * vr,
    const int & ldvr,
    int & ilo,
    int & ihi,
    float * lscale,
    float * rscale,
    float & abnrm,
    float & bbnrm,
    float * rconde,
    float * rcondv,
    float * work,
    const int & lwork,
    int * iwork,
    int * bwork,
    int & info
);

void MCLA_API f77_sggglm(
    const int & n,
    const int & m,
    const int & p,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    float * d,
    float * x,
    float * y,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sgghrd(
    const char & compq,
    const char & compz,
    const int & n,
    const int & ilo,
    const int & ihi,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    float * q,
    const int & ldq,
    float * z,
    const int & ldz,
    int & info
);

void MCLA_API f77_sgglse(
    const int & m,
    const int & n,
    const int & p,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    float * c,
    float * d,
    float * x,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sggqrf(
    const int & n,
    const int & m,
    const int & p,
    float * a,
    const int & lda,
    float * taua,
    float * b,
    const int & ldb,
    float * taub,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sggrqf(
    const int & m,
    const int & p,
    const int & n,
    float * a,
    const int & lda,
    float * taua,
    float * b,
    const int & ldb,
    float * taub,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sggsvd(
    const char & jobu,
    const char & jobv,
    const char & jobq,
    const int & m,
    const int & n,
    const int & p,
    int & k,
    int & l,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    float * alpha,
    float * beta,
    float * u,
    const int & ldu,
    float * v,
    const int & ldv,
    float * q,
    const int & ldq,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_sggsvp(
    const char & jobu,
    const char & jobv,
    const char & jobq,
    const int & m,
    const int & p,
    const int & n,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    const float & tola,
    const float & tolb,
    int & k,
    int & l,
    float * u,
    const int & ldu,
    float * v,
    const int & ldv,
    float * q,
    const int & ldq,
    int * iwork,
    float * tau,
    float * work,
    int & info
);

void MCLA_API f77_sgtcon(
    const char & norm,
    const int & n,
    const float * dl,
    const float * d,
    const float * du,
    const float * du2,
    const int * ipiv,
    const float & anorm,
    float & rcond,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_sgtrfs(
    const char & trans,
    const int & n,
    const int & nrhs,
    const float * dl,
    const float * d,
    const float * du,
    const float * dlf,
    const float * df,
    const float * duf,
    const float * du2,
    const int * ipiv,
    const float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_sgtsv(
    const int & n,
    const int & nrhs,
    float * dl,
    float * d,
    float * du,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_sgtsvx(
    const char & fact,
    const char & trans,
    const int & n,
    const int & nrhs,
    const float * dl,
    const float * d,
    const float * du,
    float * dlf,
    float * df,
    float * duf,
    float * du2,
    int * ipiv,
    const float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_sgttrf(
    const int & n,
    float * dl,
    float * d,
    float * du,
    float * du2,
    int * ipiv,
    int & info
);

void MCLA_API f77_sgttrs(
    const char & trans,
    const int & n,
    const int & nrhs,
    const float * dl,
    const float * d,
    const float * du,
    const float * du2,
    const int * ipiv,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_shgeqz(
    const char & job,
    const char & compq,
    const char & compz,
    const int & n,
    const int & ilo,
    const int & ihi,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    float * alphar,
    float * alphai,
    float * beta,
    float * q,
    const int & ldq,
    float * z,
    const int & ldz,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_shsein(
    const char & side,
    const char & eigsrc,
    const char & initv,
    int * select,
    const int & n,
    const float * h,
    const int & ldh,
    float * wr,
    const float * wi,
    float * vl,
    const int & ldvl,
    float * vr,
    const int & ldvr,
    const int & mm,
    int & m,
    float * work,
    int * ifaill,
    int * ifailr,
    int & info
);

void MCLA_API f77_shseqr(
    const char & job,
    const char & compz,
    const int & n,
    const int & ilo,
    const int & ihi,
    float * h,
    const int & ldh,
    float * wr,
    float * wi,
    float * z,
    const int & ldz,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sopgtr(
    const char & uplo,
    const int & n,
    const float * ap,
    const float * tau,
    float * q,
    const int & ldq,
    float * work,
    int & info
);

void MCLA_API f77_sopmtr(
    const char & side,
    const char & uplo,
    const char & trans,
    const int & m,
    const int & n,
    const float * ap,
    const float * tau,
    float * c,
    const int & ldc,
    float * work,
    int & info
);

void MCLA_API f77_sorgbr(
    const char & vect,
    const int & m,
    const int & n,
    const int & k,
    float * a,
    const int & lda,
    const float * tau,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sorghr(
    const int & n,
    const int & ilo,
    const int & ihi,
    float * a,
    const int & lda,
    const float * tau,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sorglq(
    const int & m,
    const int & n,
    const int & k,
    float * a,
    const int & lda,
    const float * tau,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sorgql(
    const int & m,
    const int & n,
    const int & k,
    float * a,
    const int & lda,
    const float * tau,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sorgqr(
    const int & m,
    const int & n,
    const int & k,
    float * a,
    const int & lda,
    const float * tau,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sorgrq(
    const int & m,
    const int & n,
    const int & k,
    float * a,
    const int & lda,
    const float * tau,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sorgtr(
    const char & uplo,
    const int & n,
    float * a,
    const int & lda,
    const float * tau,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sormbr(
    const char & vect,
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const float * a,
    const int & lda,
    const float * tau,
    float * c,
    const int & ldc,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sormhr(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & ilo,
    const int & ihi,
    const float * a,
    const int & lda,
    const float * tau,
    float * c,
    const int & ldc,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sormlq(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const float * a,
    const int & lda,
    const float * tau,
    float * c,
    const int & ldc,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sormql(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const float * a,
    const int & lda,
    const float * tau,
    float * c,
    const int & ldc,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sormqr(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const float * a,
    const int & lda,
    const float * tau,
    float * c,
    const int & ldc,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sormrq(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const float * a,
    const int & lda,
    const float * tau,
    float * c,
    const int & ldc,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sormrz(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const int & l,
    const float * a,
    const int & lda,
    const float * tau,
    float * c,
    const int & ldc,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_sormtr(
    const char & side,
    const char & uplo,
    const char & trans,
    const int & m,
    const int & n,
    const float * a,
    const int & lda,
    const float * tau,
    float * c,
    const int & ldc,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_spbcon(
    const char & uplo,
    const int & n,
    const int & kd,
    const float * ab,
    const int & ldab,
    const float & anorm,
    float & rcond,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_spbequ(
    const char & uplo,
    const int & n,
    const int & kd,
    const float * ab,
    const int & ldab,
    float * s,
    float & scond,
    float & amax,
    int & info
);

void MCLA_API f77_spbrfs(
    const char & uplo,
    const int & n,
    const int & kd,
    const int & nrhs,
    const float * ab,
    const int & ldab,
    const float * afb,
    const int & ldafb,
    const float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_spbstf(
    const char & uplo,
    const int & n,
    const int & kd,
    float * ab,
    const int & ldab,
    int & info
);

void MCLA_API f77_spbsv(
    const char & uplo,
    const int & n,
    const int & kd,
    const int & nrhs,
    float * ab,
    const int & ldab,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_spbsvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & kd,
    const int & nrhs,
    float * ab,
    const int & ldab,
    float * afb,
    const int & ldafb,
    char & equed,
    float * s,
    float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_spbtrf(
    const char & uplo,
    const int & n,
    const int & kd,
    float * ab,
    const int & ldab,
    int & info
);

void MCLA_API f77_spbtrs(
    const char & uplo,
    const int & n,
    const int & kd,
    const int & nrhs,
    const float * ab,
    const int & ldab,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_spocon(
    const char & uplo,
    const int & n,
    const float * a,
    const int & lda,
    const float & anorm,
    float & rcond,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_spoequ(
    const int & n,
    const float * a,
    const int & lda,
    float * s,
    float & scond,
    float & amax,
    int & info
);

void MCLA_API f77_sporfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const float * a,
    const int & lda,
    const float * af,
    const int & ldaf,
    const float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_sposv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_sposvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    float * a,
    const int & lda,
    float * af,
    const int & ldaf,
    char & equed,
    float * s,
    float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_spotrf(
    const char & uplo,
    const int & n,
    float * a,
    const int & lda,
    int & info
);

void MCLA_API f77_spotri(
    const char & uplo,
    const int & n,
    float * a,
    const int & lda,
    int & info
);

void MCLA_API f77_spotrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const float * a,
    const int & lda,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_sppcon(
    const char & uplo,
    const int & n,
    const float * ap,
    const float & anorm,
    float & rcond,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_sppequ(
    const char & uplo,
    const int & n,
    const float * ap,
    float * s,
    float & scond,
    float & amax,
    int & info
);

void MCLA_API f77_spprfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const float * ap,
    const float * afp,
    const float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_sppsv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    float * ap,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_sppsvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    float * ap,
    float * afp,
    char & equed,
    float * s,
    float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_spptrf(
    const char & uplo,
    const int & n,
    float * ap,
    int & info
);

void MCLA_API f77_spptri(
    const char & uplo,
    const int & n,
    float * ap,
    int & info
);

void MCLA_API f77_spptrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const float * ap,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_sptcon(
    const int & n,
    const float * d,
    const float * e,
    const float & anorm,
    float & rcond,
    float * work,
    int & info
);

void MCLA_API f77_spteqr(
    const char & compz,
    const int & n,
    float * d,
    float * e,
    float * z,
    const int & ldz,
    float * work,
    int & info
);

void MCLA_API f77_sptrfs(
    const int & n,
    const int & nrhs,
    const float * d,
    const float * e,
    const float * df,
    const float * ef,
    const float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    float * work,
    int & info
);

void MCLA_API f77_sptsv(
    const int & n,
    const int & nrhs,
    float * d,
    float * e,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_sptsvx(
    const char & fact,
    const int & n,
    const int & nrhs,
    const float * d,
    const float * e,
    float * df,
    float * ef,
    const float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    float * work,
    int & info
);

void MCLA_API f77_spttrf(
    const int & n,
    float * d,
    float * e,
    int & info
);

void MCLA_API f77_spttrs(
    const int & n,
    const int & nrhs,
    const float * d,
    const float * e,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_ssbev(
    const char & jobz,
    const char & uplo,
    const int & n,
    const int & kd,
    float * ab,
    const int & ldab,
    float * w,
    float * z,
    const int & ldz,
    float * work,
    int & info
);

void MCLA_API f77_ssbevd(
    const char & jobz,
    const char & uplo,
    const int & n,
    const int & kd,
    float * ab,
    const int & ldab,
    float * w,
    float * z,
    const int & ldz,
    float * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_ssbevx(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    const int & kd,
    float * ab,
    const int & ldab,
    float * q,
    const int & ldq,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    float * z,
    const int & ldz,
    float * work,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_ssbgst(
    const char & vect,
    const char & uplo,
    const int & n,
    const int & ka,
    const int & kb,
    float * ab,
    const int & ldab,
    const float * bb,
    const int & ldbb,
    float * x,
    const int & ldx,
    float * work,
    int & info
);

void MCLA_API f77_ssbgv(
    const char & jobz,
    const char & uplo,
    const int & n,
    const int & ka,
    const int & kb,
    float * ab,
    const int & ldab,
    float * bb,
    const int & ldbb,
    float * w,
    float * z,
    const int & ldz,
    float * work,
    int & info
);

void MCLA_API f77_ssbgvd(
    const char & jobz,
    const char & uplo,
    const int & n,
    const int & ka,
    const int & kb,
    float * ab,
    const int & ldab,
    float * bb,
    const int & ldbb,
    float * w,
    float * z,
    const int & ldz,
    float * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_ssbgvx(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    const int & ka,
    const int & kb,
    float * ab,
    const int & ldab,
    float * bb,
    const int & ldbb,
    float * q,
    const int & ldq,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    float * z,
    const int & ldz,
    float * work,
    int * iwork,
    const int * ifail,
    int & info
);

void MCLA_API f77_ssbtrd(
    const char & vect,
    const char & uplo,
    const int & n,
    const int & kd,
    float * ab,
    const int & ldab,
    float * d,
    float * e,
    float * q,
    const int & ldq,
    float * work,
    int & info
);

void MCLA_API f77_sspcon(
    const char & uplo,
    const int & n,
    const float * ap,
    const int * ipiv,
    const float & anorm,
    float & rcond,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_sspev(
    const char & jobz,
    const char & uplo,
    const int & n,
    float * ap,
    float * w,
    float * z,
    const int & ldz,
    float * work,
    int & info
);

void MCLA_API f77_sspevd(
    const char & jobz,
    const char & uplo,
    const int & n,
    float * ap,
    float * w,
    float * z,
    const int & ldz,
    float * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_sspevx(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    float * ap,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    float * z,
    const int & ldz,
    float * work,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_sspgst(
    const int & itype,
    const char & uplo,
    const int & n,
    float * ap,
    const float * bp,
    int & info
);

void MCLA_API f77_sspgv(
    const int & itype,
    const char & jobz,
    const char & uplo,
    const int & n,
    float * ap,
    float * bp,
    float * w,
    float * z,
    const int & ldz,
    float * work,
    int & info
);

void MCLA_API f77_sspgvd(
    const int & itype,
    const char & jobz,
    const char & uplo,
    const int & n,
    float * ap,
    float * bp,
    float * w,
    float * z,
    const int & ldz,
    float * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_sspgvx(
    const int & itype,
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    float * ap,
    float * bp,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    float * z,
    const int & ldz,
    float * work,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_ssprfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const float * ap,
    const float * afp,
    const int * ipiv,
    const float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_sspsv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    float * ap,
    int * ipiv,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_sspsvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    const float * ap,
    float * afp,
    int * ipiv,
    const float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_ssptrd(
    const char & uplo,
    const int & n,
    float * ap,
    float * d,
    float * e,
    float * tau,
    int & info
);

void MCLA_API f77_ssptrf(
    const char & uplo,
    const int & n,
    float * ap,
    int * ipiv,
    int & info
);

void MCLA_API f77_ssptri(
    const char & uplo,
    const int & n,
    float * ap,
    const int * ipiv,
    float * work,
    int & info
);

void MCLA_API f77_ssptrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const float * ap,
    const int * ipiv,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_sstebz(
    const char & range,
    const char & order,
    const int & n,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    const float * d,
    const float * e,
    int & m,
    int & nsplit,
    float * w,
    int * iblock,
    int * isplit,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_sstedc(
    const char & compz,
    const int & n,
    float * d,
    float * e,
    float * z,
    const int & ldz,
    float * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_sstegr(
    const char & jobz,
    const char & range,
    const int & n,
    float * d,
    float * e,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    float * z,
    const int & ldz,
    int * isuppz,
    float * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_sstein(
    const int & n,
    const float * d,
    const float * e,
    const int & m,
    const float * w,
    const int * iblock,
    const int * isplit,
    float * z,
    const int & ldz,
    float * work,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_ssteqr(
    const char & compz,
    const int & n,
    float * d,
    float * e,
    float * z,
    const int & ldz,
    float * work,
    int & info
);

void MCLA_API f77_ssterf(
    const int & n,
    float * d,
    float * e,
    int & info
);

void MCLA_API f77_sstev(
    const char & jobz,
    const int & n,
    float * d,
    float * e,
    float * z,
    const int & ldz,
    float * work,
    int & info
);

void MCLA_API f77_sstevd(
    const char & jobz,
    const int & n,
    float * d,
    float * e,
    float * z,
    const int & ldz,
    float * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_sstevr(
    const char & jobz,
    const char & range,
    const int & n,
    float * d,
    float * e,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    float * z,
    const int & ldz,
    int * isuppz,
    float * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_sstevx(
    const char & jobz,
    const char & range,
    const int & n,
    float * d,
    float * e,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    float * z,
    const int & ldz,
    float * work,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_ssycon(
    const char & uplo,
    const int & n,
    const float * a,
    const int & lda,
    const int * ipiv,
    const float & anorm,
    float & rcond,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_ssyev(
    const char & jobz,
    const char & uplo,
    const int & n,
    float * a,
    const int & lda,
    float * w,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_ssyevd(
    const char & jobz,
    const char & uplo,
    const int & n,
    float * a,
    const int & lda,
    float * w,
    float * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_ssyevr(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    float * a,
    const int & lda,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    float * z,
    const int & ldz,
    int * isuppz,
    float * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_ssyevx(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    float * a,
    const int & lda,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    float * z,
    const int & ldz,
    float * work,
    const int & lwork,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_ssygst(
    const int & itype,
    const char & uplo,
    const int & n,
    float * a,
    const int & lda,
    const float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_ssygv(
    const int & itype,
    const char & jobz,
    const char & uplo,
    const int & n,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    float * w,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_ssygvd(
    const int & itype,
    const char & jobz,
    const char & uplo,
    const int & n,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    float * w,
    float * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_ssygvx(
    const int & itype,
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    const float & vl,
    const float & vu,
    const int & il,
    const int & iu,
    const float & abstol,
    int & m,
    float * w,
    float * z,
    const int & ldz,
    float * work,
    const int & lwork,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_ssyrfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const float * a,
    const int & lda,
    const float * af,
    const int & ldaf,
    const int * ipiv,
    const float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_ssysv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    float * a,
    const int & lda,
    int * ipiv,
    float * b,
    const int & ldb,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_ssysvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    const float * a,
    const int & lda,
    float * af,
    const int & ldaf,
    int * ipiv,
    const float * b,
    const int & ldb,
    float * x,
    const int & ldx,
    float & rcond,
    float * ferr,
    float * berr,
    float * work,
    const int & lwork,
    int * iwork,
    int & info
);

void MCLA_API f77_ssytrd(
    const char & uplo,
    const int & n,
    float * a,
    const int & lda,
    float * d,
    float * e,
    float * tau,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_ssytrf(
    const char & uplo,
    const int & n,
    float * a,
    const int & lda,
    int * ipiv,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_ssytri(
    const char & uplo,
    const int & n,
    float * a,
    const int & lda,
    const int * ipiv,
    float * work,
    int & info
);

void MCLA_API f77_ssytrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const float * a,
    const int & lda,
    const int * ipiv,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_stbcon(
    const char & norm,
    const char & uplo,
    const char & diag,
    const int & n,
    const int & kd,
    const float * ab,
    const int & ldab,
    float & rcond,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_stbrfs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & kd,
    const int & nrhs,
    const float * ab,
    const int & ldab,
    const float * b,
    const int & ldb,
    const float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_stbtrs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & kd,
    const int & nrhs,
    const float * ab,
    const int & ldab,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_stgevc(
    const char & side,
    const char & howmny,
    const int * select,
    const int & n,
    const float * a,
    const int & lda,
    const float * b,
    const int & ldb,
    float * vl,
    const int & ldvl,
    float * vr,
    const int & ldvr,
    const int & mm,
    int & m,
    float * work,
    int & info
);

void MCLA_API f77_stgexc(
    const int & wantq,
    const int & wantz,
    const int & n,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    float * q,
    const int & ldq,
    float * z,
    const int & ldz,
    int & ifst,
    int & ilst,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_stgsen(
    const int & ijob,
    const int & wantq,
    const int & wantz,
    const int * select,
    const int & n,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    float * alphar,
    float * alphai,
    float * beta,
    float * q,
    const int & ldq,
    float * z,
    const int & ldz,
    int & m,
    float & pl,
    float & pr,
    float * dif,
    float * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_stgsja(
    const char & jobu,
    const char & jobv,
    const char & jobq,
    const int & m,
    const int & p,
    const int & n,
    const int & k,
    const int & l,
    float * a,
    const int & lda,
    float * b,
    const int & ldb,
    const float & tola,
    const float & tolb,
    float * alpha,
    float * beta,
    float * u,
    const int & ldu,
    float * v,
    const int & ldv,
    float * q,
    const int & ldq,
    float * work,
    int & ncycle,
    int & info
);

void MCLA_API f77_stgsna(
    const char & job,
    const char & howmny,
    const int * select,
    const int & n,
    const float * a,
    const int & lda,
    const float * b,
    const int & ldb,
    const float * vl,
    const int & ldvl,
    const float * vr,
    const int & ldvr,
    float * s,
    float * dif,
    const int & mm,
    int & m,
    float * work,
    const int & lwork,
    int * iwork,
    int & info
);

void MCLA_API f77_stgsyl(
    const char & trans,
    const int & ijob,
    const int & m,
    const int & n,
    const float * a,
    const int & lda,
    const float * b,
    const int & ldb,
    float * c,
    const int & ldc,
    const float * d,
    const int & ldd,
    const float * e,
    const int & lde,
    float * f,
    const int & ldf,
    float & scale,
    float & dif,
    float * work,
    const int & lwork,
    int * iwork,
    int & info
);

void MCLA_API f77_stpcon(
    const char & norm,
    const char & uplo,
    const char & diag,
    const int & n,
    const float * ap,
    float & rcond,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_stprfs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & nrhs,
    const float * ap,
    const float * b,
    const int & ldb,
    const float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_stptri(
    const char & uplo,
    const char & diag,
    const int & n,
    float * ap,
    int & info
);

void MCLA_API f77_stptrs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & nrhs,
    const float * ap,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_strcon(
    const char & norm,
    const char & uplo,
    const char & diag,
    const int & n,
    const float * a,
    const int & lda,
    float & rcond,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_strevc(
    const char & side,
    const char & howmny,
    int * select,
    const int & n,
    const float * t,
    const int & ldt,
    float * vl,
    const int & ldvl,
    float * vr,
    const int & ldvr,
    const int & mm,
    int & m,
    float * work,
    int & info
);

void MCLA_API f77_strexc(
    const char & compq,
    const int & n,
    float * t,
    const int & ldt,
    float * q,
    const int & ldq,
    int & ifst,
    int & ilst,
    float * work,
    int & info
);

void MCLA_API f77_strrfs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & nrhs,
    const float * a,
    const int & lda,
    const float * b,
    const int & ldb,
    const float * x,
    const int & ldx,
    float * ferr,
    float * berr,
    float * work,
    int * iwork,
    int & info
);

void MCLA_API f77_strsen(
    const char & job,
    const char & compq,
    const int * select,
    const int & n,
    float * t,
    const int & ldt,
    float * q,
    const int & ldq,
    float * wr,
    float * wi,
    int & m,
    float & s,
    float & sep,
    float * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_strsna(
    const char & job,
    const char & howmny,
    const int * select,
    const int & n,
    const float * t,
    const int & ldt,
    const float * vl,
    const int & ldvl,
    const float * vr,
    const int & ldvr,
    float * s,
    float * sep,
    const int & mm,
    int & m,
    float * work,
    const int & ldwork,
    int * iwork,
    int & info
);

void MCLA_API f77_strsyl(
    const char & trana,
    const char & tranb,
    const int & isgn,
    const int & m,
    const int & n,
    const float * a,
    const int & lda,
    const float * b,
    const int & ldb,
    float * c,
    const int & ldc,
    float & scale,
    int & info
);

void MCLA_API f77_strtri(
    const char & uplo,
    const char & diag,
    const int & n,
    float * a,
    const int & lda,
    int & info
);

void MCLA_API f77_strtrs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & nrhs,
    const float * a,
    const int & lda,
    float * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_stzrzf(
    const int & m,
    const int & n,
    float * a,
    const int & lda,
    float * tau,
    float * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zbdsqr(
    const char & uplo,
    const int & n,
    const int & ncvt,
    const int & nru,
    const int & ncc,
    double * d,
    double * e,
    complex_double * vt,
    const int & ldvt,
    complex_double * u,
    const int & ldu,
    complex_double * c,
    const int & ldc,
    double * rwork,
    int & info
);

void MCLA_API f77_zgbbrd(
    const char & vect,
    const int & m,
    const int & n,
    const int & ncc,
    const int & kl,
    const int & ku,
    complex_double * ab,
    const int & ldab,
    double * d,
    double * e,
    complex_double * q,
    const int & ldq,
    complex_double * pt,
    const int & ldpt,
    complex_double * c,
    const int & ldc,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zgbcon(
    const char & norm,
    const int & n,
    const int & kl,
    const int & ku,
    const complex_double * ab,
    const int & ldab,
    const int * ipiv,
    const double & anorm,
    double & rcond,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zgbequ(
    const int & m,
    const int & n,
    const int & kl,
    const int & ku,
    const complex_double * ab,
    const int & ldab,
    double * r,
    double * c,
    double & rowcnd,
    double & colcnd,
    double & amax,
    int & info
);

void MCLA_API f77_zgbrfs(
    const char & trans,
    const int & n,
    const int & kl,
    const int & ku,
    const int & nrhs,
    const complex_double * ab,
    const int & ldab,
    const complex_double * afb,
    const int & ldafb,
    const int * ipiv,
    const complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zgbsv(
    const int & n,
    const int & kl,
    const int & ku,
    const int & nrhs,
    complex_double * ab,
    const int & ldab,
    int * ipiv,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zgbsvx(
    const char & fact,
    const char & trans,
    const int & n,
    const int & kl,
    const int & ku,
    const int & nrhs,
    complex_double * ab,
    const int & ldab,
    complex_double * afb,
    const int & ldafb,
    int * ipiv,
    char & equed,
    double * r,
    double * c,
    complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zgbtrf(
    const int & m,
    const int & n,
    const int & kl,
    const int & ku,
    complex_double * ab,
    const int & ldab,
    int * ipiv,
    int & info
);

void MCLA_API f77_zgbtrs(
    const char & trans,
    const int & n,
    const int & kl,
    const int & ku,
    const int & nrhs,
    const complex_double * ab,
    const int & ldab,
    const int * ipiv,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zgebak(
    const char & job,
    const char & side,
    const int & n,
    const int & ilo,
    const int & ihi,
    const double * scale,
    const int & m,
    complex_double * v,
    const int & ldv,
    int & info
);

void MCLA_API f77_zgebal(
    const char & job,
    const int & n,
    complex_double * a,
    const int & lda,
    int & ilo,
    int & ihi,
    double * scale,
    int & info
);

void MCLA_API f77_zgebrd(
    const int & m,
    const int & n,
    complex_double * a,
    const int & lda,
    double * d,
    double * e,
    complex_double * tauq,
    complex_double * taup,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zgecon(
    const char & norm,
    const int & n,
    const complex_double * a,
    const int & lda,
    const double & anorm,
    double & rcond,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zgeequ(
    const int & m,
    const int & n,
    const complex_double * a,
    const int & lda,
    double * r,
    double * c,
    double & rowcnd,
    double & colcnd,
    double & amax,
    int & info
);

void MCLA_API f77_zgees(
    const char & jobvs,
    const char & sort,
    int (* select)(...),
    const int & n,
    complex_double * a,
    const int & lda,
    int & sdim,
    complex_double * w,
    complex_double * vs,
    const int & ldvs,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int * bwork,
    int & info
);

void MCLA_API f77_zgeesx(
    const char & jobvs,
    const char & sort,
    int (* select)(...),
    const char & sense,
    const int & n,
    complex_double * a,
    const int & lda,
    int & sdim,
    complex_double * w,
    complex_double * vs,
    const int & ldvs,
    double & rconde,
    double & rcondv,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int * bwork,
    int & info
);

void MCLA_API f77_zgeev(
    const char & jobvl,
    const char & jobvr,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * w,
    complex_double * vl,
    const int & ldvl,
    complex_double * vr,
    const int & ldvr,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int & info
);

void MCLA_API f77_zgeevx(
    const char & balanc,
    const char & jobvl,
    const char & jobvr,
    const char & sense,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * w,
    complex_double * vl,
    const int & ldvl,
    complex_double * vr,
    const int & ldvr,
    int & ilo,
    int & ihi,
    double * scale,
    double & abnrm,
    double * rconde,
    double * rcondv,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int & info
);

void MCLA_API f77_zgehrd(
    const int & n,
    const int & ilo,
    const int & ihi,
    complex_double * a,
    const int & lda,
    complex_double * tau,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zgelqf(
    const int & m,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * tau,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zgels(
    const char & trans,
    const int & m,
    const int & n,
    const int & nrhs,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zgelsd(
    const int & m,
    const int & n,
    const int & nrhs,
    const complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    double * s,
    const double & rcond,
    int & rank,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int * iwork,
    int & info
);

void MCLA_API f77_zgelss(
    const int & m,
    const int & n,
    const int & nrhs,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    double * s,
    const double & rcond,
    int & rank,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int & info
);

void MCLA_API f77_zgelsy(
    const int & m,
    const int & n,
    const int & nrhs,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    int * jpvt,
    const double & rcond,
    int & rank,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int & info
);

void MCLA_API f77_zgeqlf(
    const int & m,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * tau,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zgeqp3(
    const int & m,
    const int & n,
    complex_double * a,
    const int & lda,
    int * jpvt,
    complex_double * tau,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int & info
);

void MCLA_API f77_zgeqrf(
    const int & m,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * tau,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zgerfs(
    const char & trans,
    const int & n,
    const int & nrhs,
    const complex_double * a,
    const int & lda,
    const complex_double * af,
    const int & ldaf,
    const int * ipiv,
    const complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zgerqf(
    const int & m,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * tau,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zgesdd(
    const char & jobz,
    const int & m,
    const int & n,
    complex_double * a,
    const int & lda,
    double * s,
    complex_double * u,
    const int & ldu,
    complex_double * vt,
    const int & ldvt,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int * iwork,
    int & info
);

void MCLA_API f77_zgesv(
    const int & n,
    const int & nrhs,
    complex_double * a,
    const int & lda,
    int * ipiv,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zgesvd(
    const char & jobu,
    const char & jobvt,
    const int & m,
    const int & n,
    complex_double * a,
    const int & lda,
    double * s,
    complex_double * u,
    const int & ldu,
    complex_double * vt,
    const int & ldvt,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int & info
);

void MCLA_API f77_zgesvx(
    const char & fact,
    const char & trans,
    const int & n,
    const int & nrhs,
    complex_double * a,
    const int & lda,
    complex_double * af,
    const int & ldaf,
    int * ipiv,
    char & equed,
    double * r,
    double * c,
    complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zgetrf(
    const int & m,
    const int & n,
    complex_double * a,
    const int & lda,
    int * ipiv,
    int & info
);

void MCLA_API f77_zgetri(
    const int & n,
    complex_double * a,
    const int & lda,
    const int * ipiv,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zgetrs(
    const char & trans,
    const int & n,
    const int & nrhs,
    const complex_double * a,
    const int & lda,
    const int * ipiv,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zggbak(
    const char & job,
    const char & side,
    const int & n,
    const int & ilo,
    const int & ihi,
    const double * lscale,
    const double * rscale,
    const int & m,
    complex_double * v,
    const int & ldv,
    int & info
);

void MCLA_API f77_zggbal(
    const char & job,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    int & ilo,
    int & ihi,
    double * lscale,
    double * rscale,
    double * work,
    int & info
);

void MCLA_API f77_zgges(
    const char & jobvsl,
    const char & jobvsr,
    const char & sort,
    int (* delctg)(...),
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    int & sdim,
    complex_double * alpha,
    complex_double * beta,
    complex_double * vsl,
    const int & ldvsl,
    complex_double * vsr,
    const int & ldvsr,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int * bwork,
    int & info
);

void MCLA_API f77_zggesx(
    const char & jobvsl,
    const char & jobvsr,
    const char & sort,
    int (* delctg)(...),
    const char & sense,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    int & sdim,
    complex_double * alpha,
    complex_double * beta,
    complex_double * vsl,
    const int & ldvsl,
    complex_double * vsr,
    const int & ldvsr,
    double * rconde,
    double * rcondv,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int * iwork,
    const int & liwork,
    int * bwork,
    int & info
);

void MCLA_API f77_zggev(
    const char & jobvl,
    const char & jobvr,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    complex_double * alpha,
    complex_double * beta,
    complex_double * vl,
    const int & ldvl,
    complex_double * vr,
    const int & ldvr,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int & info
);

void MCLA_API f77_zggevx(
    const char & balanc,
    const char & jobvl,
    const char & jobvr,
    const char & sense,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    complex_double * alpha,
    complex_double * beta,
    complex_double * vl,
    const int & ldvl,
    complex_double * vr,
    const int & ldvr,
    int & ilo,
    int & ihi,
    double * lscale,
    double * rscale,
    double & abnrm,
    double & bbnrm,
    double * rconde,
    double * rcondv,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int * iwork,
    int * bwork,
    int & info
);

void MCLA_API f77_zggglm(
    const int & n,
    const int & m,
    const int & p,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    complex_double * d,
    complex_double * x,
    complex_double * y,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zgghrd(
    const char & compq,
    const char & compz,
    const int & n,
    const int & ilo,
    const int & ihi,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    complex_double * q,
    const int & ldq,
    complex_double * z,
    const int & ldz,
    int & info
);

void MCLA_API f77_zgglse(
    const int & m,
    const int & n,
    const int & p,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    complex_double * c,
    complex_double * d,
    complex_double * x,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zggqrf(
    const int & n,
    const int & m,
    const int & p,
    complex_double * a,
    const int & lda,
    complex_double * taua,
    complex_double * b,
    const int & ldb,
    complex_double * taub,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zggrqf(
    const int & m,
    const int & p,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * taua,
    complex_double * b,
    const int & ldb,
    complex_double * taub,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zggsvd(
    const char & jobu,
    const char & jobv,
    const char & jobq,
    const int & m,
    const int & n,
    const int & p,
    int & k,
    int & l,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    double * alpha,
    double * beta,
    complex_double * u,
    const int & ldu,
    complex_double * v,
    const int & ldv,
    complex_double * q,
    const int & ldq,
    complex_double * work,
    double * rwork,
    int * iwork,
    int & info
);

void MCLA_API f77_zggsvp(
    const char & jobu,
    const char & jobv,
    const char & jobq,
    const int & m,
    const int & p,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    const double & tola,
    const double & tolb,
    int & k,
    int & l,
    complex_double * u,
    const int & ldu,
    complex_double * v,
    const int & ldv,
    complex_double * q,
    const int & ldq,
    int * iwork,
    double * rwork,
    complex_double * tau,
    complex_double * work,
    int & info
);

void MCLA_API f77_zgtcon(
    const char & norm,
    const int & n,
    const complex_double * dl,
    const complex_double * d,
    const complex_double * du,
    const complex_double * du2,
    const int * ipiv,
    const double & anorm,
    double & rcond,
    complex_double * work,
    int & info
);

void MCLA_API f77_zgtrfs(
    const char & trans,
    const int & n,
    const int & nrhs,
    const complex_double * dl,
    const complex_double * d,
    const complex_double * du,
    const complex_double * dlf,
    const complex_double * df,
    const complex_double * duf,
    const complex_double * du2,
    const int * ipiv,
    const complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zgtsv(
    const int & n,
    const int & nrhs,
    complex_double * dl,
    complex_double * d,
    complex_double * du,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zgtsvx(
    const char & fact,
    const char & trans,
    const int & n,
    const int & nrhs,
    const complex_double * dl,
    const complex_double * d,
    const complex_double * du,
    complex_double * dlf,
    complex_double * df,
    complex_double * duf,
    complex_double * du2,
    int * ipiv,
    const complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zgttrf(
    const int & n,
    complex_double * dl,
    complex_double * d,
    complex_double * du,
    complex_double * du2,
    int * ipiv,
    int & info
);

void MCLA_API f77_zgttrs(
    const char & trans,
    const int & n,
    const int & nrhs,
    const complex_double * dl,
    const complex_double * d,
    const complex_double * du,
    const complex_double * du2,
    const int * ipiv,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zhbev(
    const char & jobz,
    const char & uplo,
    const int & n,
    const int & kd,
    complex_double * ab,
    const int & ldab,
    double * w,
    complex_double * z,
    const int & ldz,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zhbevd(
    const char & jobz,
    const char & uplo,
    const int & n,
    const int & kd,
    complex_double * ab,
    const int & ldab,
    double * w,
    complex_double * z,
    const int & ldz,
    complex_double * work,
    const int & lwork,
    double * rwork,
    const int & lrwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_zhbevx(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    const int & kd,
    complex_double * ab,
    const int & ldab,
    complex_double * q,
    const int & ldq,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    complex_double * z,
    const int & ldz,
    complex_double * work,
    double * rwork,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_zhbgst(
    const char & vect,
    const char & uplo,
    const int & n,
    const int & ka,
    const int & kb,
    complex_double * ab,
    const int & ldab,
    const complex_double * bb,
    const int & ldbb,
    complex_double * x,
    const int & ldx,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zhbgv(
    const char & jobz,
    const char & uplo,
    const int & n,
    const int & ka,
    const int & kb,
    complex_double * ab,
    const int & ldab,
    complex_double * bb,
    const int & ldbb,
    double * w,
    complex_double * z,
    const int & ldz,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zhbgvd(
    const char & jobz,
    const char & uplo,
    const int & n,
    const int & ka,
    const int & kb,
    complex_double * ab,
    const int & ldab,
    complex_double * bb,
    const int & ldbb,
    double * w,
    complex_double * z,
    const int & ldz,
    complex_double * work,
    const int & lwork,
    double * rwork,
    const int & lrwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_zhbgvx(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    const int & ka,
    const int & kb,
    complex_double * ab,
    const int & ldab,
    complex_double * bb,
    const int & ldbb,
    complex_double * q,
    const int & ldq,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    complex_double * z,
    const int & ldz,
    complex_double * work,
    double * rwork,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_zhbtrd(
    const char & vect,
    const char & uplo,
    const int & n,
    const int & kd,
    complex_double * ab,
    const int & ldab,
    double * d,
    double * e,
    complex_double * q,
    const int & ldq,
    complex_double * work,
    int & info
);

void MCLA_API f77_zhecon(
    const char & uplo,
    const int & n,
    const complex_double * a,
    const int & lda,
    const int * ipiv,
    const double & anorm,
    double & rcond,
    complex_double * work,
    int & info
);

void MCLA_API f77_zheev(
    const char & jobz,
    const char & uplo,
    const int & n,
    complex_double * a,
    const int & lda,
    double * w,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int & info
);

void MCLA_API f77_zheevd(
    const char & jobz,
    const char & uplo,
    const int & n,
    complex_double * a,
    const int & lda,
    double * w,
    complex_double * work,
    const int & lwork,
    double * rwork,
    const int & lrwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_zheevr(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    complex_double * a,
    const int & lda,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    complex_double * z,
    const int & ldz,
    int * isuppz,
    complex_double * work,
    const int & lwork,
    double * rwork,
    const int & lrwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_zheevx(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    complex_double * a,
    const int & lda,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    complex_double * z,
    const int & ldz,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_zhegst(
    const int & itype,
    const char & uplo,
    const int & n,
    complex_double * a,
    const int & lda,
    const complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zhegv(
    const int & itype,
    const char & jobz,
    const char & uplo,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    double * w,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int & info
);

void MCLA_API f77_zhegvd(
    const int & itype,
    const char & jobz,
    const char & uplo,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    double * w,
    complex_double * work,
    const int & lwork,
    double * rwork,
    const int & lrwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_zhegvx(
    const int & itype,
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    complex_double * z,
    const int & ldz,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_zherfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_double * a,
    const int & lda,
    const complex_double * af,
    const int & ldaf,
    const int * ipiv,
    const complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zhesv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    complex_double * a,
    const int & lda,
    int * ipiv,
    complex_double * b,
    const int & ldb,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zhesvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_double * a,
    const int & lda,
    complex_double * af,
    const int & ldaf,
    int * ipiv,
    const complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int & info
);

void MCLA_API f77_zhetrd(
    const char & uplo,
    const int & n,
    complex_double * a,
    const int & lda,
    double * d,
    double * e,
    complex_double * tau,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zhetrf(
    const char & uplo,
    const int & n,
    complex_double * a,
    const int & lda,
    int * ipiv,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zhetri(
    const char & uplo,
    const int & n,
    complex_double * a,
    const int & lda,
    const int * ipiv,
    complex_double * work,
    int & info
);

void MCLA_API f77_zhetrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_double * a,
    const int & lda,
    const int * ipiv,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zhgeqz(
    const char & job,
    const char & compq,
    const char & compz,
    const int & n,
    const int & ilo,
    const int & ihi,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    complex_double * alpha,
    complex_double * beta,
    complex_double * q,
    const int & ldq,
    complex_double * z,
    const int & ldz,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int & info
);

void MCLA_API f77_zhpcon(
    const char & uplo,
    const int & n,
    const complex_double * ap,
    const int * ipiv,
    const double & anorm,
    double & rcond,
    complex_double * work,
    int & info
);

void MCLA_API f77_zhpev(
    const char & jobz,
    const char & uplo,
    const int & n,
    complex_double * ap,
    double * w,
    complex_double * z,
    const int & ldz,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zhpevd(
    const char & jobz,
    const char & uplo,
    const int & n,
    complex_double * ap,
    double * w,
    complex_double * z,
    const int & ldz,
    complex_double * work,
    const int & lwork,
    double * rwork,
    const int & lrwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_zhpevx(
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    complex_double * ap,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    complex_double * z,
    const int & ldz,
    complex_double * work,
    double * rwork,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_zhpgst(
    const int & itype,
    const char & uplo,
    const int & n,
    complex_double * ap,
    const complex_double * bp,
    int & info
);

void MCLA_API f77_zhpgv(
    const int & itype,
    const char & jobz,
    const char & uplo,
    const int & n,
    complex_double * ap,
    complex_double * bp,
    double * w,
    complex_double * z,
    const int & ldz,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zhpgvd(
    const int & itype,
    const char & jobz,
    const char & uplo,
    const int & n,
    complex_double * ap,
    complex_double * bp,
    double * w,
    complex_double * z,
    const int & ldz,
    complex_double * work,
    const int & lwork,
    double * rwork,
    const int & lrwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_zhpgvx(
    const int & itype,
    const char & jobz,
    const char & range,
    const char & uplo,
    const int & n,
    complex_double * ap,
    complex_double * bp,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    complex_double * z,
    const int & ldz,
    complex_double * work,
    double * rwork,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_zhprfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_double * ap,
    const complex_double * afp,
    const int * ipiv,
    const complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zhpsv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    complex_double * ap,
    int * ipiv,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zhpsvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_double * ap,
    complex_double * afp,
    int * ipiv,
    const complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zhptrd(
    const char & uplo,
    const int & n,
    complex_double * ap,
    double * d,
    double * e,
    complex_double * tau,
    int & info
);

void MCLA_API f77_zhptrf(
    const char & uplo,
    const int & n,
    complex_double * ap,
    int * ipiv,
    int & info
);

void MCLA_API f77_zhptri(
    const char & uplo,
    const int & n,
    complex_double * ap,
    const int * ipiv,
    complex_double * work,
    int & info
);

void MCLA_API f77_zhptrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_double * ap,
    const int * ipiv,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zhsein(
    const char & side,
    const char & eigsrc,
    const char & initv,
    const int * select,
    const int & n,
    const complex_double * h,
    const int & ldh,
    complex_double * w,
    complex_double * vl,
    const int & ldvl,
    complex_double * vr,
    const int & ldvr,
    const int & mm,
    int & m,
    complex_double * work,
    double * rwork,
    int * ifaill,
    int * ifailr,
    int & info
);

void MCLA_API f77_zhseqr(
    const char & job,
    const char & compz,
    const int & n,
    const int & ilo,
    const int & ihi,
    complex_double * h,
    const int & ldh,
    complex_double * w,
    complex_double * z,
    const int & ldz,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zpbcon(
    const char & uplo,
    const int & n,
    const int & kd,
    const complex_double * ab,
    const int & ldab,
    const double & anorm,
    double & rcond,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zpbequ(
    const char & uplo,
    const int & n,
    const int & kd,
    const complex_double * ab,
    const int & ldab,
    double * s,
    double & scond,
    double & amax,
    int & info
);

void MCLA_API f77_zpbrfs(
    const char & uplo,
    const int & n,
    const int & kd,
    const int & nrhs,
    const complex_double * ab,
    const int & ldab,
    const complex_double * afb,
    const int & ldafb,
    const complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zpbstf(
    const char & uplo,
    const int & n,
    const int & kd,
    complex_double * ab,
    const int & ldab,
    int & info
);

void MCLA_API f77_zpbsv(
    const char & uplo,
    const int & n,
    const int & kd,
    const int & nrhs,
    complex_double * ab,
    const int & ldab,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zpbsvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & kd,
    const int & nrhs,
    complex_double * ab,
    const int & ldab,
    complex_double * afb,
    const int & ldafb,
    char & equed,
    double * s,
    complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zpbtrf(
    const char & uplo,
    const int & n,
    const int & kd,
    complex_double * ab,
    const int & ldab,
    int & info
);

void MCLA_API f77_zpbtrs(
    const char & uplo,
    const int & n,
    const int & kd,
    const int & nrhs,
    const complex_double * ab,
    const int & ldab,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zpocon(
    const char & uplo,
    const int & n,
    const complex_double * a,
    const int & lda,
    const double & anorm,
    double & rcond,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zpoequ(
    const int & n,
    const complex_double * a,
    const int & lda,
    double * s,
    double & scond,
    double & amax,
    int & info
);

void MCLA_API f77_zporfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_double * a,
    const int & lda,
    const complex_double * af,
    const int & ldaf,
    const complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zposv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zposvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    complex_double * a,
    const int & lda,
    complex_double * af,
    const int & ldaf,
    char & equed,
    double * s,
    complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zpotrf(
    const char & uplo,
    const int & n,
    complex_double * a,
    const int & lda,
    int & info
);

void MCLA_API f77_zpotri(
    const char & uplo,
    const int & n,
    complex_double * a,
    const int & lda,
    int & info
);

void MCLA_API f77_zpotrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zppcon(
    const char & uplo,
    const int & n,
    const complex_double * ap,
    const double & anorm,
    double & rcond,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zppequ(
    const char & uplo,
    const int & n,
    const complex_double * ap,
    double * s,
    double & scond,
    double & amax,
    int & info
);

void MCLA_API f77_zpprfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_double * ap,
    const complex_double * afp,
    const complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zppsv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    complex_double * ap,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zppsvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    complex_double * ap,
    complex_double * afp,
    char & equed,
    double * s,
    complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zpptrf(
    const char & uplo,
    const int & n,
    complex_double * ap,
    int & info
);

void MCLA_API f77_zpptri(
    const char & uplo,
    const int & n,
    complex_double * ap,
    int & info
);

void MCLA_API f77_zpptrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_double * ap,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zptcon(
    const int & n,
    const double * d,
    const complex_double * e,
    const double & anorm,
    double & rcond,
    double * rwork,
    int & info
);

void MCLA_API f77_zpteqr(
    const char & compz,
    const int & n,
    double * d,
    double * e,
    complex_double * z,
    const int & ldz,
    double * work,
    int & info
);

void MCLA_API f77_zptrfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const double * d,
    const complex_double * e,
    const double * df,
    const complex_double * ef,
    const complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zptsv(
    const int & n,
    const int & nrhs,
    double * d,
    complex_double * e,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zptsvx(
    const char & fact,
    const int & n,
    const int & nrhs,
    const double * d,
    const complex_double * e,
    double * df,
    complex_double * ef,
    const complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zpttrf(
    const int & n,
    double * d,
    complex_double * e,
    int & info
);

void MCLA_API f77_zpttrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const double * d,
    const complex_double * e,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zspcon(
    const char & uplo,
    const int & n,
    const complex_double * ap,
    const int * ipiv,
    const double & anorm,
    double & rcond,
    complex_double * work,
    int & info
);

void MCLA_API f77_zsprfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_double * ap,
    const complex_double * afp,
    const int * ipiv,
    const complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zspsv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    complex_double * ap,
    int * ipiv,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zspsvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_double * ap,
    complex_double * afp,
    int * ipiv,
    const complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zsptrf(
    const char & uplo,
    const int & n,
    complex_double * ap,
    int * ipiv,
    int & info
);

void MCLA_API f77_zsptri(
    const char & uplo,
    const int & n,
    complex_double * ap,
    const int * ipiv,
    complex_double * work,
    int & info
);

void MCLA_API f77_zsptrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_double * ap,
    const int * ipiv,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_zstedc(
    const char & compz,
    const int & n,
    double * d,
    double * e,
    complex_double * z,
    const int & ldz,
    complex_double * work,
    const int & lwork,
    double * rwork,
    const int & lrwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_zstegr(
    const char & jobz,
    const char & range,
    const int & n,
    double * d,
    double * e,
    const double & vl,
    const double & vu,
    const int & il,
    const int & iu,
    const double & abstol,
    int & m,
    double * w,
    complex_double * z,
    const int & ldz,
    int * isuppz,
    double * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_zstein(
    const int & n,
    const double * d,
    const double * e,
    const int & m,
    const double * w,
    const int * iblock,
    const int * isplit,
    complex_double * z,
    const int & ldz,
    double * work,
    int * iwork,
    int * ifail,
    int & info
);

void MCLA_API f77_zsteqr(
    const char & compz,
    const int & n,
    double * d,
    double * e,
    complex_double * z,
    const int & ldz,
    double * work,
    int & info
);

void MCLA_API f77_zsycon(
    const char & uplo,
    const int & n,
    const complex_double * a,
    const int & lda,
    const int * ipiv,
    const double & anorm,
    double & rcond,
    complex_double * work,
    int & info
);

void MCLA_API f77_zsyrfs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_double * a,
    const int & lda,
    const complex_double * af,
    const int & ldaf,
    const int * ipiv,
    const complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_zsysv(
    const char & uplo,
    const int & n,
    const int & nrhs,
    complex_double * a,
    const int & lda,
    int * ipiv,
    complex_double * b,
    const int & ldb,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zsysvx(
    const char & fact,
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_double * a,
    const int & lda,
    complex_double * af,
    const int & ldaf,
    int * ipiv,
    const complex_double * b,
    const int & ldb,
    complex_double * x,
    const int & ldx,
    double & rcond,
    double * ferr,
    double * berr,
    complex_double * work,
    const int & lwork,
    double * rwork,
    int & info
);

void MCLA_API f77_zsytrf(
    const char & uplo,
    const int & n,
    complex_double * a,
    const int & lda,
    int * ipiv,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zsytri(
    const char & uplo,
    const int & n,
    complex_double * a,
    const int & lda,
    const int * ipiv,
    complex_double * work,
    int & info
);

void MCLA_API f77_zsytrs(
    const char & uplo,
    const int & n,
    const int & nrhs,
    const complex_double * a,
    const int & lda,
    const int * ipiv,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_ztbcon(
    const char & norm,
    const char & uplo,
    const char & diag,
    const int & n,
    const int & kd,
    const complex_double * ab,
    const int & ldab,
    double & rcond,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_ztbrfs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & kd,
    const int & nrhs,
    const complex_double * ab,
    const int & ldab,
    const complex_double * b,
    const int & ldb,
    const complex_double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_ztbtrs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & kd,
    const int & nrhs,
    const complex_double * ab,
    const int & ldab,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_ztgevc(
    const char & side,
    const char & howmny,
    const int * select,
    const int & n,
    const complex_double * a,
    const int & lda,
    const complex_double * b,
    const int & ldb,
    complex_double * vl,
    const int & ldvl,
    complex_double * vr,
    const int & ldvr,
    const int & mm,
    int & m,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_ztgexc(
    const int & wantq,
    const int & wantz,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    complex_double * q,
    const int & ldq,
    complex_double * z,
    const int & ldz,
    int & ifst,
    int & ilst,
    int & info
);

void MCLA_API f77_ztgsen(
    const int & ijob,
    const int & wantq,
    const int & wantz,
    const int * select,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    complex_double * alpha,
    complex_double * beta,
    complex_double * q,
    const int & ldq,
    complex_double * z,
    const int & ldz,
    int & m,
    double & pl,
    double & pr,
    double * dif,
    complex_double * work,
    const int & lwork,
    int * iwork,
    const int & liwork,
    int & info
);

void MCLA_API f77_ztgsja(
    const char & jobu,
    const char & jobv,
    const char & jobq,
    const int & m,
    const int & p,
    const int & n,
    const int & k,
    const int & l,
    complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    const double & tola,
    const double & tolb,
    double * alpha,
    double * beta,
    complex_double * u,
    const int & ldu,
    complex_double * v,
    const int & ldv,
    complex_double * q,
    const int & ldq,
    complex_double * work,
    int & ncycle,
    int & info
);

void MCLA_API f77_ztgsna(
    const char & job,
    const char & howmny,
    const int * select,
    const int & n,
    const complex_double * a,
    const int & lda,
    const complex_double * b,
    const int & ldb,
    const complex_double * vl,
    const int & ldvl,
    const complex_double * vr,
    const int & ldvr,
    double * s,
    double * dif,
    const int & mm,
    int & m,
    complex_double * work,
    const int & lwork,
    int * iwork,
    int & info
);

void MCLA_API f77_ztgsyl(
    const char & trans,
    const int & ijob,
    const int & m,
    const int & n,
    const complex_double * a,
    const int & lda,
    const complex_double * b,
    const int & ldb,
    complex_double * c,
    const int & ldc,
    const complex_double * d,
    const int & ldd,
    const complex_double * e,
    const int & lde,
    complex_double * f,
    const int & ldf,
    double & scale,
    double & dif,
    complex_double * work,
    const int & lwork,
    int * iwork,
    int & info
);

void MCLA_API f77_ztpcon(
    const char & norm,
    const char & uplo,
    const char & diag,
    const int & n,
    const complex_double * ap,
    double & rcond,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_ztprfs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & nrhs,
    const complex_double * ap,
    const complex_double * b,
    const int & ldb,
    const complex_double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_ztptri(
    const char & uplo,
    const char & diag,
    const int & n,
    complex_double * ap,
    int & info
);

void MCLA_API f77_ztptrs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & nrhs,
    const complex_double * ap,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_ztrcon(
    const char & norm,
    const char & uplo,
    const char & diag,
    const int & n,
    const complex_double * a,
    const int & lda,
    double & rcond,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_ztrevc(
    const char & side,
    const char & howmny,
    const int * select,
    const int & n,
    complex_double * t,
    const int & ldt,
    complex_double * vl,
    const int & ldvl,
    complex_double * vr,
    const int & ldvr,
    const int & mm,
    int & m,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_ztrexc(
    const char & compq,
    const int & n,
    complex_double * t,
    const int & ldt,
    complex_double * q,
    const int & ldq,
    const int & ifst,
    const int & ilst,
    int & info
);

void MCLA_API f77_ztrrfs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & nrhs,
    const complex_double * a,
    const int & lda,
    const complex_double * b,
    const int & ldb,
    const complex_double * x,
    const int & ldx,
    double * ferr,
    double * berr,
    complex_double * work,
    double * rwork,
    int & info
);

void MCLA_API f77_ztrsen(
    const char & job,
    const char & compq,
    const int * select,
    const int & n,
    complex_double * t,
    const int & ldt,
    complex_double * q,
    const int & ldq,
    complex_double * w,
    int & m,
    double & s,
    double & sep,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_ztrsna(
    const char & job,
    const char & howmny,
    const int * select,
    const int & n,
    const complex_double * t,
    const int & ldt,
    const complex_double * vl,
    const int & ldvl,
    const complex_double * vr,
    const int & ldvr,
    double * s,
    double * sep,
    const int & mm,
    int & m,
    complex_double * work,
    const int & ldwork,
    double * rwork,
    int & info
);

void MCLA_API f77_ztrsyl(
    const char & trana,
    const char & tranb,
    const int & isgn,
    const int & m,
    const int & n,
    const complex_double * a,
    const int & lda,
    const complex_double * b,
    const int & ldb,
    complex_double * c,
    const int & ldc,
    double & scale,
    int & info
);

void MCLA_API f77_ztrtri(
    const char & uplo,
    const char & diag,
    const int & n,
    complex_double * a,
    const int & lda,
    int & info
);

void MCLA_API f77_ztrtrs(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & nrhs,
    const complex_double * a,
    const int & lda,
    complex_double * b,
    const int & ldb,
    int & info
);

void MCLA_API f77_ztzrzf(
    const int & m,
    const int & n,
    complex_double * a,
    const int & lda,
    complex_double * tau,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zungbr(
    const char & vect,
    const int & m,
    const int & n,
    const int & k,
    complex_double * a,
    const int & lda,
    const complex_double * tau,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zunghr(
    const int & n,
    const int & ilo,
    const int & ihi,
    complex_double * a,
    const int & lda,
    const complex_double * tau,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zunglq(
    const int & m,
    const int & n,
    const int & k,
    complex_double * a,
    const int & lda,
    const complex_double * tau,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zungql(
    const int & m,
    const int & n,
    const int & k,
    complex_double * a,
    const int & lda,
    const complex_double * tau,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zungqr(
    const int & m,
    const int & n,
    const int & k,
    complex_double * a,
    const int & lda,
    const complex_double * tau,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zungrq(
    const int & m,
    const int & n,
    const int & k,
    complex_double * a,
    const int & lda,
    const complex_double * tau,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zungtr(
    const char & uplo,
    const int & n,
    complex_double * a,
    const int & lda,
    const complex_double * tau,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zunmbr(
    const char & vect,
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const complex_double * a,
    const int & lda,
    const complex_double * tau,
    complex_double * c,
    const int & ldc,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zunmhr(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & ilo,
    const int & ihi,
    const complex_double * a,
    const int & lda,
    const complex_double * tau,
    complex_double * c,
    const int & ldc,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zunmlq(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const complex_double * a,
    const int & lda,
    const complex_double * tau,
    complex_double * c,
    const int & ldc,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zunmql(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const complex_double * a,
    const int & lda,
    const complex_double * tau,
    complex_double * c,
    const int & ldc,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zunmqr(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const complex_double * a,
    const int & lda,
    const complex_double * tau,
    complex_double * c,
    const int & ldc,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zunmrq(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const complex_double * a,
    const int & lda,
    const complex_double * tau,
    complex_double * c,
    const int & ldc,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zunmrz(
    const char & side,
    const char & trans,
    const int & m,
    const int & n,
    const int & k,
    const int & l,
    const complex_double * a,
    const int & lda,
    const complex_double * tau,
    complex_double * c,
    const int & ldc,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zunmtr(
    const char & side,
    const char & uplo,
    const char & trans,
    const int & m,
    const int & n,
    const complex_double * a,
    const int & lda,
    const complex_double * tau,
    complex_double * c,
    const int & ldc,
    complex_double * work,
    const int & lwork,
    int & info
);

void MCLA_API f77_zupgtr(
    const char & uplo,
    const int & n,
    const complex_double * ap,
    const complex_double * tau,
    complex_double * q,
    const int & ldq,
    complex_double * work,
    int & info
);

void MCLA_API f77_zupmtr(
    const char & side,
    const char & uplo,
    const char & trans,
    const int & m,
    const int & n,
    const complex_double * ap,
    const complex_double * tau,
    complex_double * c,
    const int & ldc,
    complex_double * work,
    int & info
);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // F77_LAPACK_H

/// @}
