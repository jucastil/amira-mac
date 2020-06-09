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
#ifndef F77_BLAS_H
#define F77_BLAS_H

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

void MCLA_API f77_caxpy(
    const int & n,
    const complex_float & ca,
    const complex_float * cx,
    const int & incx,
    const complex_float * cy,
    const int & incy
);

void MCLA_API f77_ccopy(
    const int & n,
    const complex_float * cx,
    const int & incx,
    const complex_float * cy,
    const int & incy
);

complex_float MCLA_API f77_cdotc(
    const int & n,
    const complex_float * cx,
    const int & incx,
    const complex_float * cy,
    const int & incy
);

complex_float MCLA_API f77_cdotu(
    const int & n,
    const complex_float * cx,
    const int & incx,
    const complex_float * cy,
    const int & incy
);

void MCLA_API f77_cgbmv(
    const char & trans,
    const int & m,
    const int & n,
    const int & kl,
    const int & ku,
    const complex_float & alpha,
    const complex_float * a,
    const int & lda,
    const complex_float * x,
    const int & incx,
    const complex_float & beta,
    const complex_float * y,
    const int & incy
);

void MCLA_API f77_cgemm(
    const char & transa,
    const char & transb,
    const int & m,
    const int & n,
    const int & k,
    const complex_float & alpha,
    const complex_float * a,
    const int & lda,
    const complex_float * b,
    const int & ldb,
    const complex_float & beta,
    const complex_float * c,
    const int & ldc
);

void MCLA_API f77_cgemv(
    const char & trans,
    const int & m,
    const int & n,
    const complex_float & alpha,
    const complex_float * a,
    const int & lda,
    const complex_float * x,
    const int & incx,
    const complex_float & beta,
    const complex_float * y,
    const int & incy
);

void MCLA_API f77_cgerc(
    const int & m,
    const int & n,
    const complex_float & alpha,
    const complex_float * x,
    const int & incx,
    const complex_float * y,
    const int & incy,
    const complex_float * a,
    const int & lda
);

void MCLA_API f77_cgeru(
    const int & m,
    const int & n,
    const complex_float & alpha,
    const complex_float * x,
    const int & incx,
    const complex_float * y,
    const int & incy,
    const complex_float * a,
    const int & lda
);

void MCLA_API f77_chbmv(
    const char & uplo,
    const int & n,
    const int & k,
    const complex_float & alpha,
    const complex_float * a,
    const int & lda,
    const complex_float * x,
    const int & incx,
    const complex_float & beta,
    const complex_float * y,
    const int & incy
);

void MCLA_API f77_chemm(
    const char & side,
    const char & uplo,
    const int & m,
    const int & n,
    const complex_float & alpha,
    const complex_float * a,
    const int & lda,
    const complex_float * b,
    const int & ldb,
    const complex_float & beta,
    const complex_float * c,
    const int & ldc
);

void MCLA_API f77_chemv(
    const char & uplo,
    const int & n,
    const complex_float & alpha,
    const complex_float * a,
    const int & lda,
    const complex_float * x,
    const int & incx,
    const complex_float & beta,
    const complex_float * y,
    const int & incy
);

void MCLA_API f77_cher(
    const char & uplo,
    const int & n,
    const float & alpha,
    const complex_float * x,
    const int & incx,
    const complex_float * a,
    const int & lda
);

void MCLA_API f77_cher2(
    const char & uplo,
    const int & n,
    const complex_float & alpha,
    const complex_float * x,
    const int & incx,
    const complex_float * y,
    const int & incy,
    const complex_float * a,
    const int & lda
);

void MCLA_API f77_cher2k(
    const char & uplo,
    const char & trans,
    const int & n,
    const int & k,
    const complex_float & alpha,
    const complex_float * a,
    const int & lda,
    const complex_float * b,
    const int & ldb,
    const float & beta,
    const complex_float * c,
    const int & ldc
);

void MCLA_API f77_cherk(
    const char & uplo,
    const char & trans,
    const int & n,
    const int & k,
    const float & alpha,
    const complex_float * a,
    const int & lda,
    const float & beta,
    const complex_float * c,
    const int & ldc
);

void MCLA_API f77_chpmv(
    const char & uplo,
    const int & n,
    const complex_float & alpha,
    const complex_float * ap,
    const complex_float * x,
    const int & incx,
    const complex_float & beta,
    const complex_float * y,
    const int & incy
);

void MCLA_API f77_chpr(
    const char & uplo,
    const int & n,
    const float & alpha,
    const complex_float * x,
    const int & incx,
    const complex_float * ap
);

void MCLA_API f77_chpr2(
    const char & uplo,
    const int & n,
    const complex_float & alpha,
    const complex_float * x,
    const int & incx,
    const complex_float * y,
    const int & incy,
    const complex_float * ap
);

void MCLA_API f77_cscal(
    const int & n,
    const complex_float & ca,
    const complex_float * cx,
    const int & incx
);

void MCLA_API f77_csscal(
    const int & n,
    const float & sa,
    const complex_float * cx,
    const int & incx
);

void MCLA_API f77_cswap(
    const int & n,
    const complex_float * cx,
    const int & incx,
    const complex_float * cy,
    const int & incy
);

void MCLA_API f77_csymm(
    const char & side,
    const char & uplo,
    const int & m,
    const int & n,
    const complex_float & alpha,
    const complex_float * a,
    const int & lda,
    const complex_float * b,
    const int & ldb,
    const complex_float & beta,
    const complex_float * c,
    const int & ldc
);

void MCLA_API f77_csyr2k(
    const char & uplo,
    const char & trans,
    const int & n,
    const int & k,
    const complex_float & alpha,
    const complex_float * a,
    const int & lda,
    const complex_float * b,
    const int & ldb,
    const complex_float & beta,
    const complex_float * c,
    const int & ldc
);

void MCLA_API f77_csyrk(
    const char & uplo,
    const char & trans,
    const int & n,
    const int & k,
    const complex_float & alpha,
    const complex_float * a,
    const int & lda,
    const complex_float & beta,
    const complex_float * c,
    const int & ldc
);

void MCLA_API f77_ctbmv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & k,
    const complex_float * a,
    const int & lda,
    const complex_float * x,
    const int & incx
);

void MCLA_API f77_ctbsv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & k,
    const complex_float * a,
    const int & lda,
    const complex_float * x,
    const int & incx
);

void MCLA_API f77_ctpmv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const complex_float * ap,
    const complex_float * x,
    const int & incx
);

void MCLA_API f77_ctpsv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const complex_float * ap,
    const complex_float * x,
    const int & incx
);

void MCLA_API f77_ctrmm(
    const char & side,
    const char & uplo,
    const char & transa,
    const char & diag,
    const int & m,
    const int & n,
    const complex_float & alpha,
    const complex_float * a,
    const int & lda,
    const complex_float * b,
    const int & ldb
);

void MCLA_API f77_ctrmv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const complex_float * a,
    const int & lda,
    const complex_float * x,
    const int & incx
);

void MCLA_API f77_ctrsm(
    const char & side,
    const char & uplo,
    const char & transa,
    const char & diag,
    const int & m,
    const int & n,
    const complex_float & alpha,
    const complex_float * a,
    const int & lda,
    const complex_float * b,
    const int & ldb
);

void MCLA_API f77_ctrsv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const complex_float * a,
    const int & lda,
    const complex_float * x,
    const int & incx
);

double MCLA_API f77_dasum(
    const int & n,
    const double * dx,
    const int & incx
);

void MCLA_API f77_daxpy(
    const int & n,
    const double & da,
    const double * dx,
    const int & incx,
    const double * dy,
    const int & incy
);

void MCLA_API f77_dcopy(
    const int & n,
    const double * dx,
    const int & incx,
    const double * dy,
    const int & incy
);

double MCLA_API f77_ddot(
    const int & n,
    const double * dx,
    const int & incx,
    const double * dy,
    const int & incy
);

void MCLA_API f77_dgbmv(
    const char & trans,
    const int & m,
    const int & n,
    const int & kl,
    const int & ku,
    const double & alpha,
    const double * a,
    const int & lda,
    const double * x,
    const int & incx,
    const double & beta,
    const double * y,
    const int & incy
);

void MCLA_API f77_dgemm(
    const char & transa,
    const char & transb,
    const int & m,
    const int & n,
    const int & k,
    const double & alpha,
    const double * a,
    const int & lda,
    const double * b,
    const int & ldb,
    const double & beta,
    const double * c,
    const int & ldc
);

void MCLA_API f77_dgemv(
    const char & trans,
    const int & m,
    const int & n,
    const double & alpha,
    const double * a,
    const int & lda,
    const double * x,
    const int & incx,
    const double & beta,
    const double * y,
    const int & incy
);

void MCLA_API f77_dger(
    const int & m,
    const int & n,
    const double & alpha,
    const double * x,
    const int & incx,
    const double * y,
    const int & incy,
    const double * a,
    const int & lda
);

double MCLA_API f77_dnrm2(
    const int & n,
    const double * x,
    const int & incx
);

void MCLA_API f77_drot(
    const int & n,
    const double * dx,
    const int & incx,
    const double * dy,
    const int & incy,
    const double & c,
    const double & s
);

void MCLA_API f77_drotg(
    const double & da,
    const double & db,
    const double & c,
    const double & s
);

void MCLA_API f77_dsbmv(
    const char & uplo,
    const int & n,
    const int & k,
    const double & alpha,
    const double * a,
    const int & lda,
    const double * x,
    const int & incx,
    const double & beta,
    const double * y,
    const int & incy
);

void MCLA_API f77_dscal(
    const int & n,
    const double & da,
    const double * dx,
    const int & incx
);

void MCLA_API f77_dspmv(
    const char & uplo,
    const int & n,
    const double & alpha,
    const double * ap,
    const double * x,
    const int & incx,
    const double & beta,
    const double * y,
    const int & incy
);

void MCLA_API f77_dspr(
    const char & uplo,
    const int & n,
    const double & alpha,
    const double * x,
    const int & incx,
    const double * ap
);

void MCLA_API f77_dspr2(
    const char & uplo,
    const int & n,
    const double & alpha,
    const double * x,
    const int & incx,
    const double * y,
    const int & incy,
    const double * ap
);

void MCLA_API f77_dswap(
    const int & n,
    const double * dx,
    const int & incx,
    const double * dy,
    const int & incy
);

void MCLA_API f77_dsymm(
    const char & side,
    const char & uplo,
    const int & m,
    const int & n,
    const double & alpha,
    const double * a,
    const int & lda,
    const double * b,
    const int & ldb,
    const double & beta,
    const double * c,
    const int & ldc
);

void MCLA_API f77_dsymv(
    const char & uplo,
    const int & n,
    const double & alpha,
    const double * a,
    const int & lda,
    const double * x,
    const int & incx,
    const double & beta,
    const double * y,
    const int & incy
);

void MCLA_API f77_dsyr(
    const char & uplo,
    const int & n,
    const double & alpha,
    const double * x,
    const int & incx,
    const double * a,
    const int & lda
);

void MCLA_API f77_dsyr2(
    const char & uplo,
    const int & n,
    const double & alpha,
    const double * x,
    const int & incx,
    const double * y,
    const int & incy,
    const double * a,
    const int & lda
);

void MCLA_API f77_dsyr2k(
    const char & uplo,
    const char & trans,
    const int & n,
    const int & k,
    const double & alpha,
    const double * a,
    const int & lda,
    const double * b,
    const int & ldb,
    const double & beta,
    const double * c,
    const int & ldc
);

void MCLA_API f77_dsyrk(
    const char & uplo,
    const char & trans,
    const int & n,
    const int & k,
    const double & alpha,
    const double * a,
    const int & lda,
    const double & beta,
    const double * c,
    const int & ldc
);

void MCLA_API f77_dtbmv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & k,
    const double * a,
    const int & lda,
    const double * x,
    const int & incx
);

void MCLA_API f77_dtbsv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & k,
    const double * a,
    const int & lda,
    const double * x,
    const int & incx
);

void MCLA_API f77_dtpmv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const double * ap,
    const double * x,
    const int & incx
);

void MCLA_API f77_dtpsv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const double * ap,
    const double * x,
    const int & incx
);

void MCLA_API f77_dtrmm(
    const char & side,
    const char & uplo,
    const char & transa,
    const char & diag,
    const int & m,
    const int & n,
    const double & alpha,
    const double * a,
    const int & lda,
    const double * b,
    const int & ldb
);

void MCLA_API f77_dtrmv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const double * a,
    const int & lda,
    const double * x,
    const int & incx
);

void MCLA_API f77_dtrsm(
    const char & side,
    const char & uplo,
    const char & transa,
    const char & diag,
    const int & m,
    const int & n,
    const double & alpha,
    const double * a,
    const int & lda,
    const double * b,
    const int & ldb
);

void MCLA_API f77_dtrsv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const double * a,
    const int & lda,
    const double * x,
    const int & incx
);

double MCLA_API f77_dzasum(
    const int & n,
    const complex_double * zx,
    const int & incx
);

double MCLA_API f77_dznrm2(
    const int & n,
    const complex_double * x,
    const int & incx
);

int MCLA_API f77_icamax(
    const int & n,
    const complex_float * cx,
    const int & incx
);

int MCLA_API f77_idamax(
    const int & n,
    const double * dx,
    const int & incx
);

int MCLA_API f77_isamax(
    const int & n,
    const float * sx,
    const int & incx
);

int MCLA_API f77_izamax(
    const int & n,
    const complex_double * zx,
    const int & incx
);

float MCLA_API f77_sasum(
    const int & n,
    const float * sx,
    const int & incx
);

void MCLA_API f77_saxpy(
    const int & n,
    const float & sa,
    const float * sx,
    const int & incx,
    const float * sy,
    const int & incy
);

float MCLA_API f77_scasum(
    const int & n,
    const complex_float * cx,
    const int & incx
);

float MCLA_API f77_scnrm2(
    const int & n,
    const complex_float * x,
    const int & incx
);

void MCLA_API f77_scopy(
    const int & n,
    const float * sx,
    const int & incx,
    const float * sy,
    const int & incy
);

float MCLA_API f77_sdot(
    const int & n,
    const float * sx,
    const int & incx,
    const float * sy,
    const int & incy
);

void MCLA_API f77_sgbmv(
    const char & trans,
    const int & m,
    const int & n,
    const int & kl,
    const int & ku,
    const float & alpha,
    const float * a,
    const int & lda,
    const float * x,
    const int & incx,
    const float & beta,
    const float * y,
    const int & incy
);

void MCLA_API f77_sgemm(
    const char & transa,
    const char & transb,
    const int & m,
    const int & n,
    const int & k,
    const float & alpha,
    const float * a,
    const int & lda,
    const float * b,
    const int & ldb,
    const float & beta,
    const float * c,
    const int & ldc
);

void MCLA_API f77_sgemv(
    const char & trans,
    const int & m,
    const int & n,
    const float & alpha,
    const float * a,
    const int & lda,
    const float * x,
    const int & incx,
    const float & beta,
    const float * y,
    const int & incy
);

void MCLA_API f77_sger(
    const int & m,
    const int & n,
    const float & alpha,
    const float * x,
    const int & incx,
    const float * y,
    const int & incy,
    const float * a,
    const int & lda
);

float MCLA_API f77_snrm2(
    const int & n,
    const float * x,
    const int & incx
);

void MCLA_API f77_srot(
    const int & n,
    const float * sx,
    const int & incx,
    const float * sy,
    const int & incy,
    const float & c,
    const float & s
);

void MCLA_API f77_srotg(
    const float & sa,
    const float & sb,
    const float & c,
    const float & s
);

void MCLA_API f77_ssbmv(
    const char & uplo,
    const int & n,
    const int & k,
    const float & alpha,
    const float * a,
    const int & lda,
    const float * x,
    const int & incx,
    const float & beta,
    const float * y,
    const int & incy
);

void MCLA_API f77_sscal(
    const int & n,
    const float & sa,
    const float * sx,
    const int & incx
);

void MCLA_API f77_sspmv(
    const char & uplo,
    const int & n,
    const float & alpha,
    const float * ap,
    const float * x,
    const int & incx,
    const float & beta,
    const float * y,
    const int & incy
);

void MCLA_API f77_sspr(
    const char & uplo,
    const int & n,
    const float & alpha,
    const float * x,
    const int & incx,
    const float * ap
);

void MCLA_API f77_sspr2(
    const char & uplo,
    const int & n,
    const float & alpha,
    const float * x,
    const int & incx,
    const float * y,
    const int & incy,
    const float * ap
);

void MCLA_API f77_sswap(
    const int & n,
    const float * sx,
    const int & incx,
    const float * sy,
    const int & incy
);

void MCLA_API f77_ssymm(
    const char & side,
    const char & uplo,
    const int & m,
    const int & n,
    const float & alpha,
    const float * a,
    const int & lda,
    const float * b,
    const int & ldb,
    const float & beta,
    const float * c,
    const int & ldc
);

void MCLA_API f77_ssymv(
    const char & uplo,
    const int & n,
    const float & alpha,
    const float * a,
    const int & lda,
    const float * x,
    const int & incx,
    const float & beta,
    const float * y,
    const int & incy
);

void MCLA_API f77_ssyr(
    const char & uplo,
    const int & n,
    const float & alpha,
    const float * x,
    const int & incx,
    const float * a,
    const int & lda
);

void MCLA_API f77_ssyr2(
    const char & uplo,
    const int & n,
    const float & alpha,
    const float * x,
    const int & incx,
    const float * y,
    const int & incy,
    const float * a,
    const int & lda
);

void MCLA_API f77_ssyr2k(
    const char & uplo,
    const char & trans,
    const int & n,
    const int & k,
    const float & alpha,
    const float * a,
    const int & lda,
    const float * b,
    const int & ldb,
    const float & beta,
    const float * c,
    const int & ldc
);

void MCLA_API f77_ssyrk(
    const char & uplo,
    const char & trans,
    const int & n,
    const int & k,
    const float & alpha,
    const float * a,
    const int & lda,
    const float & beta,
    const float * c,
    const int & ldc
);

void MCLA_API f77_stbmv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & k,
    const float * a,
    const int & lda,
    const float * x,
    const int & incx
);

void MCLA_API f77_stbsv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & k,
    const float * a,
    const int & lda,
    const float * x,
    const int & incx
);

void MCLA_API f77_stpmv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const float * ap,
    const float * x,
    const int & incx
);

void MCLA_API f77_stpsv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const float * ap,
    const float * x,
    const int & incx
);

void MCLA_API f77_strmm(
    const char & side,
    const char & uplo,
    const char & transa,
    const char & diag,
    const int & m,
    const int & n,
    const float & alpha,
    const float * a,
    const int & lda,
    const float * b,
    const int & ldb
);

void MCLA_API f77_strmv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const float * a,
    const int & lda,
    const float * x,
    const int & incx
);

void MCLA_API f77_strsm(
    const char & side,
    const char & uplo,
    const char & transa,
    const char & diag,
    const int & m,
    const int & n,
    const float & alpha,
    const float * a,
    const int & lda,
    const float * b,
    const int & ldb
);

void MCLA_API f77_strsv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const float * a,
    const int & lda,
    const float * x,
    const int & incx
);

void MCLA_API f77_zaxpy(
    const int & n,
    const complex_double & za,
    const complex_double * zx,
    const int & incx,
    const complex_double * zy,
    const int & incy
);

void MCLA_API f77_zcopy(
    const int & n,
    const complex_double * zx,
    const int & incx,
    const complex_double * zy,
    const int & incy
);

complex_double MCLA_API f77_zdotc(
    const int & n,
    const complex_double * zx,
    const int & incx,
    const complex_double * zy,
    const int & incy
);

complex_double MCLA_API f77_zdotu(
    const int & n,
    const complex_double * zx,
    const int & incx,
    const complex_double * zy,
    const int & incy
);

void MCLA_API f77_zdscal(
    const int & n,
    const double & da,
    const complex_double * zx,
    const int & incx
);

void MCLA_API f77_zgbmv(
    const char & trans,
    const int & m,
    const int & n,
    const int & kl,
    const int & ku,
    const complex_double & alpha,
    const complex_double * a,
    const int & lda,
    const complex_double * x,
    const int & incx,
    const complex_double & beta,
    const complex_double * y,
    const int & incy
);

void MCLA_API f77_zgemm(
    const char & transa,
    const char & transb,
    const int & m,
    const int & n,
    const int & k,
    const complex_double & alpha,
    const complex_double * a,
    const int & lda,
    const complex_double * b,
    const int & ldb,
    const complex_double & beta,
    const complex_double * c,
    const int & ldc
);

void MCLA_API f77_zgemv(
    const char & trans,
    const int & m,
    const int & n,
    const complex_double & alpha,
    const complex_double * a,
    const int & lda,
    const complex_double * x,
    const int & incx,
    const complex_double & beta,
    const complex_double * y,
    const int & incy
);

void MCLA_API f77_zgerc(
    const int & m,
    const int & n,
    const complex_double & alpha,
    const complex_double * x,
    const int & incx,
    const complex_double * y,
    const int & incy,
    const complex_double * a,
    const int & lda
);

void MCLA_API f77_zgeru(
    const int & m,
    const int & n,
    const complex_double & alpha,
    const complex_double * x,
    const int & incx,
    const complex_double * y,
    const int & incy,
    const complex_double * a,
    const int & lda
);

void MCLA_API f77_zhbmv(
    const char & uplo,
    const int & n,
    const int & k,
    const complex_double & alpha,
    const complex_double * a,
    const int & lda,
    const complex_double * x,
    const int & incx,
    const complex_double & beta,
    const complex_double * y,
    const int & incy
);

void MCLA_API f77_zhemm(
    const char & side,
    const char & uplo,
    const int & m,
    const int & n,
    const complex_double & alpha,
    const complex_double * a,
    const int & lda,
    const complex_double * b,
    const int & ldb,
    const complex_double & beta,
    const complex_double * c,
    const int & ldc
);

void MCLA_API f77_zhemv(
    const char & uplo,
    const int & n,
    const complex_double & alpha,
    const complex_double * a,
    const int & lda,
    const complex_double * x,
    const int & incx,
    const complex_double & beta,
    const complex_double * y,
    const int & incy
);

void MCLA_API f77_zher(
    const char & uplo,
    const int & n,
    const double & alpha,
    const complex_double * x,
    const int & incx,
    const complex_double * a,
    const int & lda
);

void MCLA_API f77_zher2(
    const char & uplo,
    const int & n,
    const complex_double & alpha,
    const complex_double * x,
    const int & incx,
    const complex_double * y,
    const int & incy,
    const complex_double * a,
    const int & lda
);

void MCLA_API f77_zher2k(
    const char & uplo,
    const char & trans,
    const int & n,
    const int & k,
    const complex_double & alpha,
    const complex_double * a,
    const int & lda,
    const complex_double * b,
    const int & ldb,
    const double & beta,
    const complex_double * c,
    const int & ldc
);

void MCLA_API f77_zherk(
    const char & uplo,
    const char & trans,
    const int & n,
    const int & k,
    const double & alpha,
    const complex_double * a,
    const int & lda,
    const double & beta,
    const complex_double * c,
    const int & ldc
);

void MCLA_API f77_zhpmv(
    const char & uplo,
    const int & n,
    const complex_double & alpha,
    const complex_double * ap,
    const complex_double * x,
    const int & incx,
    const complex_double & beta,
    const complex_double * y,
    const int & incy
);

void MCLA_API f77_zhpr(
    const char & uplo,
    const int & n,
    const double & alpha,
    const complex_double * x,
    const int & incx,
    const complex_double * ap
);

void MCLA_API f77_zhpr2(
    const char & uplo,
    const int & n,
    const complex_double & alpha,
    const complex_double * x,
    const int & incx,
    const complex_double * y,
    const int & incy,
    const complex_double * ap
);

void MCLA_API f77_zscal(
    const int & n,
    const complex_double & za,
    const complex_double * zx,
    const int & incx
);

void MCLA_API f77_zswap(
    const int & n,
    const complex_double * zx,
    const int & incx,
    const complex_double * zy,
    const int & incy
);

void MCLA_API f77_zsymm(
    const char & side,
    const char & uplo,
    const int & m,
    const int & n,
    const complex_double & alpha,
    const complex_double * a,
    const int & lda,
    const complex_double * b,
    const int & ldb,
    const complex_double & beta,
    const complex_double * c,
    const int & ldc
);

void MCLA_API f77_zsyr2k(
    const char & uplo,
    const char & trans,
    const int & n,
    const int & k,
    const complex_double & alpha,
    const complex_double * a,
    const int & lda,
    const complex_double * b,
    const int & ldb,
    const complex_double & beta,
    const complex_double * c,
    const int & ldc
);

void MCLA_API f77_zsyrk(
    const char & uplo,
    const char & trans,
    const int & n,
    const int & k,
    const complex_double & alpha,
    const complex_double * a,
    const int & lda,
    const complex_double & beta,
    const complex_double * c,
    const int & ldc
);

void MCLA_API f77_ztbmv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & k,
    const complex_double * a,
    const int & lda,
    const complex_double * x,
    const int & incx
);

void MCLA_API f77_ztbsv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const int & k,
    const complex_double * a,
    const int & lda,
    const complex_double * x,
    const int & incx
);

void MCLA_API f77_ztpmv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const complex_double * ap,
    const complex_double * x,
    const int & incx
);

void MCLA_API f77_ztpsv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const complex_double * ap,
    const complex_double * x,
    const int & incx
);

void MCLA_API f77_ztrmm(
    const char & side,
    const char & uplo,
    const char & transa,
    const char & diag,
    const int & m,
    const int & n,
    const complex_double & alpha,
    const complex_double * a,
    const int & lda,
    const complex_double * b,
    const int & ldb
);

void MCLA_API f77_ztrmv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const complex_double * a,
    const int & lda,
    const complex_double * x,
    const int & incx
);

void MCLA_API f77_ztrsm(
    const char & side,
    const char & uplo,
    const char & transa,
    const char & diag,
    const int & m,
    const int & n,
    const complex_double & alpha,
    const complex_double * a,
    const int & lda,
    const complex_double * b,
    const int & ldb
);

void MCLA_API f77_ztrsv(
    const char & uplo,
    const char & trans,
    const char & diag,
    const int & n,
    const complex_double * a,
    const int & lda,
    const complex_double * x,
    const int & incx
);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // F77_BLAS_H

/// @}
