/*
 *  Author:      Jake Cooper.
 *  Date:        November 4th, 2013
 *  File name:   VectorManipulation.c
 *  Description: Vector linear algebra functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* function sqrt() is defined in <math.h> */
#include <stdbool.h>
#include <float.h>

/* constant FLT_EPSILON is defined in <float.h> */
#define BIG_EPSILON  (0.5)

typedef int Index;
typedef float Item;

#define VSIZE     (4)
typedef Item Vector[VSIZE];

void setVector1(Vector V, Item x) {
	/* V = {x, y} */
	V[0] = x; V[1] = 0.0; V[2] = 0.0; V[3] = 0.0;
} /* setVector1 */

void setVector2(Vector V, Item x, Item y) {
	/* V = {x, y} */
	V[0] = x; V[1] = y;	V[2] = 0.0; V[3] = 0.0;
} /* setVector2 */

void setVector3(Vector V, Item x, Item y, Item z) {
	/* V = {x, y, z} */
	V[0] = x; V[1] = y; V[2] = z; V[3] = 0.0;
} /* setVector3 */

void setVector4(Vector V, Item x, Item y, Item z, Item h) {
	/* V = {x, y, z} */
	V[0] = x; V[1] = y; V[2] = z; V[3] = h;
} /* setVector4 */

void printVector(Vector V, Index size) {
	/* output V[0], V[1], V[2], ..., V[size-1] */
	Index k;
	printf("   ");
	for (k=0; k<size; k++) printf("%.1f  ", V[k]);
	printf("\n");
} /* printVector */

void printVectorHighPrecision(Vector V, Index size) {
	/* output V[0], V[1], V[2], ..., V[size-1] */
	Index k;
	printf("   ");
	for (k=0; k<size; k++) printf("%.7f  ", V[k]);
	printf("\n");
} /* printVectorHighPrecision */

bool equalVectors(Vector V1, Vector V2, Index size, Item eps) {
	/* return true if V1 == V2; false otherwise */
	Index k;
	for (k=0; k<size; k++) {
		if (fabs(V1[k]-V2[k]) > eps) {
			// Vectors are not equal
			return false;
		} /* if */
	} /* for */
	return true;
} /* equalVectors */

bool equalVectors2(Vector V1, Item x, Item y, Item eps) {
	/* return true if V1 == {x, y}; false otherwise */
	Index k;
	Vector V2 = {x, y};
	for (k=0; k<2; k++) {
		if (fabs(V1[k]-V2[k]) > eps) {
			printf("Vectors are not equal\n");
			return false;
		} /* if */
	} /* for */
	return true;
} /* equalVectors2 */

bool equalVectors3(Vector V1, Item x, Item y, Item z, Item eps) {
	/* return true if V1 == {x, y, z}; false otherwise */
	Index k;
	Vector V2 = {x, y, z};
	for (k=0; k<3; k++) {
		if (fabs(V1[k]-V2[k]) > eps) {
			printf("Vectors are not equal\n");
			return false;
		} /* if */
	} /* for */
	return true;
} /* equalVectors3 */

bool equalVectors4(Vector V1, Item x, Item y, Item z, Item h, Item eps) {
	/* return true if V1 == {x, y, z, h}; false otherwise */
	Index k;
	Vector V2 = {x, y, z, h};
	for (k=0; k<4; k++) {
		if (fabs(V1[k]-V2[k]) > eps) {
			printf("Vectors are not equal\n");
			return false;
		} /* if */
	} /* for */
	return true;
} /* equalVectors4 */

Item sumItems(Vector V, Index size) {
	/* return sum(V[0], V[1], V[2], ..., V[size-1]) */
	Index k;
	Item sum = 0.0;
	for(k=0; k<size; k++) sum += V[k];
	return sum;
} /* sumItems */

void initIndexVector(Vector V, Index size) {
	/*  V[0]=0, V[1]=1, V[2]=2, ..., V[size-1]=size-1) */
	Index k;
	for (k=0; k<size; k++) V[k] = (Item)k;
} /* initIndexVector */

void initVectorWithValue(Vector V, Index size, Item val) {
	/*  V[0]=val, V[1]=val, V[2]=val, ..., V[size-1]=val) */
	Index k;
	for(k=0; k<size; k++) V[k]=val;
} /* initVectorWithValue */

void allOnesVector(Vector V, Index size) {
	/*  V[0]=1, V[1]=1, V[2]=1, ..., V[size-1]=1) */
	initVectorWithValue(V, size, 1);
} /* allOnesVector */

void addScalarToVector(Vector V, Index size, Item s) {
	/*  V[0]=V[0]+s, V[1]+s, V[2]+s, ..., V[size-1]=V[size-1]+s) */
	Index k;
	for(k=0; k<size; k++) V[k] += s;
} /* addScalarToVector */

void mulVectorByScalar(Vector V, Index size, Item s) {
	/*  V[0]=V[0]*s, V[1]*s, V[2]*s, ..., V[size-1]=V[size-1]*s) */
	Index k;
	for(k=0; k<size; k++) V[k] *= s;
} /* mulVectorByScalar */

void addVectors(Vector V1, Vector V2, Vector V3, Index size) {
	/*  V3[0]=V1[0]+v2[0], V3[1]=V1[1]+v2[1], V3[2]=V1[2]+v2[2], ..., V3[size-1]=V1[size-1]+v2[size-1]) */
	Index k;
	for(k=0; k<size; k++) V3[k]= V1[k]+ V2[k];
} /* addVectors */

void mulVectors(Vector V1, Vector V2, Vector V3, Index size) {
	/*  V3[0]=V1[0]*v2[0], V3[1]=V1[1]*v2[1], V3[2]=V1[2]*v2[2], ..., V3[size-1]=V1[size-1]*v2[size-1]) */
	Index k;
	for(k=0; k<size; k++) V3[k]= V1[k] * V2[k];
} /* mulVectors */

Item dotProduct(Vector V1, Vector V2, Index size) {
	/*  return sum(V1[0]*v2[0], V1[1]*v2[1], V1[2]*v2[2], ..., V1[size-1]*v2[size-1]) */
	Index k;
	Item dotProduct = 0.0;
	for(k=0; k<size; k++) dotProduct = V1[k]*V2[k] + dotProduct;
	return dotProduct;
} /* dotProduct */

Item vectorLength(Vector V, Index size) {
	/* also known as the L2 norm of a vector */
	/* return |V| = square-root(V[0]*v[0], V[1]*v[1], V[2]*v[2], ..., V[size-1]*v[size-1]) */
	Index k;
	Item magV = 0.0;
	for(k=0; k<size; k++) magV = V[k]*V[k] + magV;
	magV = sqrt(magV);
	/* the implementation of this function requires sqrt() from <math.h> */
	return magV;
} /* vectorLength */

void normalizeVector(Vector V, Index size) {
	/* V[0]/|V|, V[1]/|V|, V[2]/|V|, ..., V[size-1]/|V| */
	Index k;
	Item magV;
	magV = vectorLength(V,size);
	for(k=0; k<size; k++)V[k] = V[k]/magV;
} /* normalizeVector */




