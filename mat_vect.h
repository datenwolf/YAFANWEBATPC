
#ifndef _MAT_VECT_H
#define _MAT_VECT_H



/**********************************************************
 *
 * TYPES DECLARATION
 *
 *********************************************************/

typedef struct {
    float x,y,z;
} p3d_type, *p3d_ptr_type;



/**********************************************************
 *
 * FUNCTIONS DECLARATION
 *
 *********************************************************/

extern void VectCreate (p3d_ptr_type p_start, p3d_ptr_type p_end, p3d_ptr_type p_vector);
extern float VectLength (p3d_ptr_type p_vector);
extern void VectNormalize(p3d_ptr_type p_vector);
extern float VectScalarProduct (p3d_ptr_type p_vector1,p3d_ptr_type p_vector2);
extern void VectDotProduct (p3d_ptr_type p_vector1,p3d_ptr_type p_vector2,p3d_ptr_type p_normal);

#endif
