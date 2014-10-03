#include "jb_math.h"

#define SOLVE_MATRIX 1
//#define SPLINE_CUBIC 1

#ifdef SOLVE_MATRIX

#include "jb_math.h"

JBFLOAT x[]=
{
	1., 3., 2., 16.,
	2., 4., 8., 18.,
	3., -1, 4., 0.
};
JBFLOAT y[]={3., 5., -1.};

main()
{
	jbm_solve_matrix(x, 3);
	printf("x0="FWF2"x0="FWF"\n", x[3], y[0]);
	printf("x1="FWF2"x1="FWF"\n", x[7], y[1]);
	printf("x2="FWF2"x2="FWF"\n", x[11], y[2]);
}

#endif

#ifdef SPLINE_CUBIC

#define FWF2 FWF" "
#include "jb_math.h"

JBFLOAT x[]={0., 1., 2., 3., 4., 5.};
JBFLOAT y[]={0., 1., 3., 6., 8., 7.};

JBFLOAT A[]={1.,2.,-1.};
JBFLOAT B[]={3.,1.,4.,7.};
JBFLOAT C[]={-1.,2.,-3.,4.,2.};
JBFLOAT D[]={-2.,-1.,3.,1.};
JBFLOAT E[]={-3.,1.,2.};
JBFLOAT H[]={-20.,13.,14.,52.,48.};

main()
{
	int i;
	FILE *file;
	JBFLOAT *c, *d, *e;
	jbm_solve_pentadiagonal_matrix(A,B,C,D,E,H,5);
	for (i = 0; i < 5; ++i) printf("i=%d x="FWF"\n", i, H[i]);
	jbm_spline_cubic(x, y, 6, &c, &d, &e);
	file = fopen("out", "w");
	for (i = 0; i<5; ++i)
	{
		printf("i=%d c="FWF" d="FWF" e="FWF"\n", i, c[i], d[i], e[i]);
		fprintf(file, FWF2 FWF2 FWF2 FWF2 FWF"\n",
			x[i], y[i], c[i], d[i], e[i]);
	}
	fclose(file);
	jbm_regression(x, y, 6, &c, 2);
	for (i = 0; i <= 2; ++i) printf("i=%d c="FWF"\n", i, c[i]);
	jbm_regression(x, y, 6, &c, 3);
	for (i = 0; i <= 3; ++i) printf("i=%d c="FWF"\n", i, c[i]);
}

#else

#ifdef TRANSVERSAL_SECTION_REGIONS

int n=24;
JBFLOAT l[25]=
{0.,-1.,-1.,0.,2.,0.,0.,2.,1.,3.,2.,4.,5.,5.,3.,3.,6.,4.,2.,3.,6.,6.,7.,5.,5.};
JBFLOAT z[25]=
{6.,6.,3.,5.,3.,3.,2.,2.,3.,2.,0.,0.,1.,3.,3.,4.,3.,5.,4.,6.,5.,4.,5.,6.,7.};

main()
{
	JBFLOAT *zz;
	int *ni,*nj,*nij,nmax,nmin;
	stderr=fopen("log","w");
	jbm_transversal_section_regions(l,z,n,&zz,&ni,&nj,&nij,&nmax,&nmin);
}

#endif

#ifdef FARRAY_MEAN_SQUARE_ERROR

int na=6,nr=2;
JBFLOAT xa[7]={0.,1.,2.,3.,4.,5.,6.};
JBFLOAT ya[7]={3.,2.,-1.,4.,7.,3.,1.};
JBFLOAT xr[3]={1.5,3.2,4.8};
JBFLOAT yr[3]={2.,3.,1.};

main()
{
	printf("MSE = "FWL"\n",jbm_farray_mean_square_error(xa,ya,na,xr,yr,nr));
}

#endif

#ifdef VARRAY_MEAN_SQUARE_ERROR

typedef struct
{
	JBFLOAT x,y,z;
} P3;

typedef struct
{
	JBFLOAT x,y;
} P2;

int na=6,nr=2;
P2 va[7]={0.,3.,1.,2.,2.,-1.,3.,4.,4.,7.,5.,3.,6.,1.};
P3 vr[3]={1.5,2.,0.,3.2,3.,0.,4.8,1.,0};

main()
{
	printf("MSE = "FWL"\n",
		jbm_varray_mean_square_error
			(&(va->x),&(va->y),sizeof(P2),na,
			&(vr->x),&(vr->y),sizeof(P3),nr));
}

#endif

#ifdef FILE_MEAN_SQUARE_ERROR

main()
{
	printf
		("MSE = "FWL"\n",jbm_file_mean_square_error("msea",1,2,2,"mser",1,2,3));
}

#endif

#ifdef INDEX_SORT

#include <time.h>

#define N 40000000
#define SEED 7

//JBFLOAT y[15]={13.,-2.,5.,3.7,18.3,8.,9.,12.,7.,14.,-8.,3.,3.,12.,-7.};

main()
{
	int i,j,k,*ni;
	JBFLOAT *x,*z;
	GRand *rand;
	clock_t t0,tf;
/*
	ni=(int*)malloc(N*sizeof(int));
	for (i=0; i<15; ++i) ni[i]=i;
	jbm_index_sort_merge(y,ni,14);
	for (i=0; i<15; ++i) printf("i=%d ni=%d xi="FWF"\n",i,ni[i],y[ni[i]]);
*/
	rand = g_rand_new_with_seed(SEED);
	ni=(int*)malloc(N*sizeof(int));
	x=(JBFLOAT*)malloc(N*sizeof(JBFLOAT));
	z=(JBFLOAT*)malloc(N*sizeof(JBFLOAT));
	for (i=0; i<N; ++i)
	{
		ni[i]=i;
		x[i]=g_rand_double(rand);
		z[i]=sin(M_PI*x[i]);
	}
/*
	printf("Index sort interchange\n");
	t0=clock();
	jbm_index_sort_interchange(x,ni,N-1);
	tf=clock();
	printf("time=%lg\n",((double)(tf-t0))/CLOCKS_PER_SEC);
	for (i=0; i<N; ++i) ni[i]=i;
	printf("Index sort insertion\n");
	t0=clock();
	jbm_index_sort_insertion(x,ni,N-1);
	tf=clock();
	printf("time=%lg\n",((double)(tf-t0))/CLOCKS_PER_SEC);
	for (i=0; i<N; ++i) ni[i]=i;
	printf("Index sort merge\n");
	for (i=0; i<N; ++i) ni[i]=i;
	t0=clock();
	jbm_index_sort_merge(x,ni,N-1);
	tf=clock();
	printf("Rand time=%lg\n",j,((double)(tf-t0))/CLOCKS_PER_SEC);
	for (i=0; i<N; ++i) ni[i]=i;
	t0=clock();
	jbm_index_sort_merge(z,ni,N-1);
	tf=clock();
	printf("Sin time=%lg\n",j,((double)(tf-t0))/CLOCKS_PER_SEC);
*/
	printf("Index sort flash\n");
	for (i=0; i<N; ++i) ni[i]=i;
	t0=clock();
	jbm_index_sort_flash(x,ni,N-1);
	tf=clock();
	printf("Rand time=%lg\n",((double)(tf-t0))/CLOCKS_PER_SEC);
	for (i=0; i<N; ++i) ni[i]=i;
	t0=clock();
	jbm_index_sort_flash(z,ni,N-1);
	tf=clock();
	printf("Sin time=%lg\n",((double)(tf-t0))/CLOCKS_PER_SEC);
	for (i=0; ++i<N;) if (z[ni[i]]>z[ni[i-1]])
		printf("i=%d x1="FWF" x2="FWF"\n",i,x[ni[i]],x[ni[i-1]]);
}

#endif

#endif