#!/usr/bin/env bash

for i in dbl sqr opposite reciprocal sign abs copysign hypot frexp exp2n \
	ldexp cbrtwc cbrt exp2wc exp2 exp exp10 expm1wc expm1 log2wc log2 log \
	log10 pown pow sinwc coswc tanwc sincoswc atanwc atan atan2 asin acos \
	sinh cosh tanh asinh acosh atanh sin cos sincos tan erfwc erfcwc erf \
	erfc integral {extra,inter}polate v{2,3}_length \
	solve_{quadratic,cubic{reduced,}} \
	flux_limiter{,_{total,null,centred,superbee,minmod,Van{Leer,Albada},minsuper,supermin,monotonized_central,mean}} \
	reduce_{add,max,min,maxmin} mod;
do
	for j in f32 f64 4xf32 2xf64 8xf32 4xf64 16xf32 8xf64 nxf32 nxf64; do
		sed -i "s/${i}_${j}/${j}_${i}/g" */*.{h,c}
	done
done
for k in f32 f64 4xf32 2xf64 8xf32 4xf64 16xf32 8xf64 nxf32 nxf64; do
	for ((i = 1; i < 30; ++i)); do
		sed -i "s/polynomial_${i}_${k}/${k}_polynomial_${i}/g" \
			*/*.{h,c}
	done
	for ((i = 1; i < 30; ++i)); do
		for ((j = 0; j < i; ++j)); do
			sed -i "s/rational_${i}_${j}_${k}/${k}_rational_${i}_${j}/g" \
				*/*.{h,c}
		done
	done
done
for i in add sub mul{,1} div{,1} dot dbl sqr sum max min maxmin; do
       for j in f32 f64; do	
		sed -i "s/array_${i}_${j}/array_${j}_${i}/g" */*.{h,c}
	done
done
