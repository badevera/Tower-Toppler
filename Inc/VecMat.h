// VecQuaMat.h, copyright (c) 2024 Jules Bloomenthal, all rights reserved; commercial use requires license.
// 2D, 3D, 4D vector classes, 3x3 and 4x4 matrix classes, quaternion class

#ifndef VEC_MAT_HDR
#define VEC_MAT_HDR

#include <float.h>
#include <math.h>
#include <iostream>

// vector representation
//     vec2/vec3/vec4 v;        // defaults to zero vector
// access
//     float f = v[i];
// class operations
//     -v                       // negate v
//     a-b                      // subtract b from a
//     a+b                      // add v
//     *s                       // multiply by s
//     /s                       // divide by s
//     a*b                      // dot product of a and b
//     reflexively: -=, +=, *=, /=
// non-class operations
//     dot                      // dot product
//     length                   // magnitude
//     normalize                // set to unit length
//     cross                    // cross product

//  2D vector

class vec2 {
public:
	float x, y;
	// constructors
	vec2(float s = 0) : x(s), y(s) { }
	vec2(float x, float y) : x(x), y(y) { }
	vec2(double x, double y) : x((float) x), y((float) y) { }
	vec2(float *p) : x(p[0]), y(p[1]) { }
	vec2(const vec2 &v) : x(v.x), y(v.y) { }
	vec2(const float *p) : x(p[0]), y(p[1]) { }
	vec2(int xa, int ya) { x = (float) xa; y = (float) ya; }
	// access
	float &operator [] (int i) { return *(&x+i); }
	const float operator [] (int i) const { return *(&x+i); }
	operator const float* () const { return static_cast<const float*>(&x); }
	operator float* () { return static_cast<float*>(&x); }
	// operations
	vec2 operator - () const { return vec2(-x, -y); }
	vec2 operator + (const vec2 &v) const { return vec2(x+v.x, y+v.y); }
	vec2 operator - (const vec2 &v) const { return vec2(x-v.x, y-v.y); }
	vec2 operator * (float s) const { return vec2(s*x, s*y); }
	vec2 operator * (const vec2 &v) const { return vec2(x*v.x, y*v.y); }
	friend vec2 operator * (float s, const vec2 &v) { return v*s; }
	vec2 operator / (float s) const { float r = 1.f/s; return *this*r; }
	vec2 operator / (const vec2 &v) const { return vec2(x/v.x, y/v.y); }
	// reflexive
	vec2 &operator += (const vec2 &v) { x += v.x; y += v.y; return *this; }
	vec2 &operator -= (const vec2 &v) { x -= v.x; y -= v.y; return *this; }
	vec2 &operator *= (float s) { x *= s; y *= s; return *this; }
	vec2 &operator *= (const vec2 &v) { x *= v.x; y *= v.y; return *this; }
	vec2 &operator /= (float s) { float r = 1.f/s; *this *= r; return *this; }
};

inline float dot(const vec2 &a, const vec2 &b) { return a.x*b.x+a.y*b.y; }
inline float cross(const vec2 &v1, const vec2 &v2) { return v1.x*v2.y-v1.y*v2.x; }
inline float length(const vec2 &v) { return sqrt(dot(v,v)); }
inline vec2 normalize(const vec2 &v) { return v/length(v); }

inline float Bounds(vec2 *points, int npoints, vec2 &min, vec2 &max) {
	max = -(min = vec2(FLT_MAX));
	for (int i = 0; i < npoints; i++) {
		vec2 p = points[i];
		min = vec2(min.x < p.x? min.x : p.x, min.y < p.y? min.y : p.y);
		max = vec2(max.x > p.x? max.x : p.x, max.y > p.y? max.y : p.y);
	}
	vec2 dif = max-min;
	return dif.x > dif.y? dif.x : dif.y;
}

//  3D vector

class vec3 {
public:
	float  x, y, z;
	// constructors
	vec3(float s = 0) : x(s), y(s), z(s) { }
	vec3(float x, float y, float z = 0) : x(x), y(y), z(z) { }
	vec3(const vec3 &v) { x = v.x; y = v.y; z = v.z; }
	vec3(const vec2 &v, float f = 0) { x = v.x; y = v.y; z = f; }
	vec3(const float *p) : x(p[0]), y(p[1]), z(p[2]) { }
   // access
	float &operator [] (int i) { return *(&x+i); } // causes ambiguity
	const float operator [] (int i) const { return *(&x+i); }
	// arithmetic
	vec3 operator - () const { return vec3(-x, -y, -z); }
	vec3 operator + (const vec3 &v) const { return vec3(x+v.x, y+v.y, z+v.z); }
	vec3 operator - (const vec3 &v) const { return vec3(x-v.x, y-v.y, z-v.z); }
	vec3 operator * (float s) const { return vec3(s*x, s*y, s*z); }
	vec3 operator * (const vec3 &v) const { return vec3(x*v.x, y*v.y, z*v.z); }
	friend vec3 operator * (float s, const vec3 &v) { return v*s; }
	vec3 operator / (float s) const { float r = 1.f/s; return *this * r; }
	vec3 operator / (const vec3 &v) const { return vec3(x/v.x, y/v.y, z/v.z); }
	// reflexive
	vec3 &operator += (const vec3 &v) { x += v.x; y += v.y; z += v.z; return *this; }
	vec3 &operator -= (const vec3 &v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	vec3 &operator *= (float s) { x *= s; y *= s; z *= s; return *this; }
	vec3 &operator *= (const vec3 &v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
	vec3 &operator /= (float s) { float r = 1.f/s; *this *= r; return *this; }
};

inline float dot(const vec3 &a, const vec3 &b) { return a.x*b.x+a.y*b.y+a.z*b.z; }
inline float length(const vec3 &v) { return sqrt(dot(v,v)); }
inline vec3 normalize(const vec3 &v) { return v/length(v); }
inline vec3 cross(const vec3 &a, const vec3 &b) { return vec3(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x); }
	// right-handed cross-product

inline float Bounds(vec3 *points, int npoints, vec3 &min, vec3 &max) {
	max = -(min = vec3(FLT_MAX));
	for (int i = 0; i < npoints; i++) {
		vec3 p = points[i];
		min = vec3(min.x < p.x? min.x : p.x, min.y < p.y? min.y : p.y, min.z < p.z? min.z : p.z);
		max = vec3(max.x > p.x? max.x : p.x, max.y > p.y? max.y : p.y, max.z > p.z? max.z : p.z);
	}
	vec3 dif = max-min;
	return dif.x > dif.y? (dif.z > dif.x? dif.z : dif.x) : (dif.z > dif.y? dif.z : dif.y);
}

// 4D vector

class vec4 {
public:
	float x, y, z, w;
	// constructors
	vec4(float s = 0) : x(s), y(s), z(s), w(s) { }
	vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
	vec4(const vec4 &v) { x = v.x; y = v.y;  z = v.z;  w = v.w; }
	vec4(float *p) : x(p[0]), y(p[1]), z(p[2]), w(p[3]) { }
	vec4(const vec2 &v, float z = 0, float w = 1) : x(v.x), y(v.y), z(z), w(w) { }
	vec4(const vec3 &v, float w = 1) : x(v.x), y(v.y), z(v.z), w(w) { }
	// access
	float &operator [] (int i) { return *(&x+i); }
	const float operator [] (int i) const { return *(&x+i); }
	operator const float* () const { return static_cast<const float*>(&x); }
	operator float* () { return static_cast<float*>(&x); }
	// arithmetic
	vec4 operator - () const { return vec4(-x, -y, -z, -w); }
	vec4 operator + (const vec4 &v) const { return vec4(x+v.x, y+v.y, z+v.z, w+v.w); }
	vec4 operator - (const vec4 &v) const { return vec4(x-v.x, y-v.y, z-v.z, w-v.w); }
	vec4 operator * (float s) const { return vec4(s*x, s*y, s*z, s*w); }
	vec4 operator * (const vec4 &v) const { return vec4(x*v.x, y*v.y, z*v.z, w*v.z); }
	friend vec4 operator * (float s, const vec4& v) { return v*s; }
	vec4 operator / (float s) const { float r = 1.f/s; return *this*r; }
	// reflexive
	vec4 &operator += (const vec4 &v) { x += v.x;  y += v.y;  z += v.z;  w += v.w; return *this; }
	vec4 &operator -= (const vec4 &v) { x -= v.x;  y -= v.y;  z -= v.z;  w -= v.w; return *this; }
	vec4 &operator *= (float s) { x *= s;  y *= s;  z *= s;  w *= s; return *this; }
	vec4 &operator *= (const vec4 &v) { x *= v.x, y *= v.y, z *= v.z, w *= v.w; return *this; }
	vec4 &operator /= (float s) { float r = 1.f/s; *this *= r; return *this; }
};

inline float dot(const vec4 &a, const vec4 &b) { return a.x*b.x+a.y*b.y+a.z*b.z+a.w*b.w; }
inline float length(const vec4 &v) { return sqrt(dot(v, v)); }
inline vec4 normalize(const vec4 &v) { return v/length(v); }

inline vec2 Vec2(vec4 v) { return vec2(v.x, v.y); }
inline vec3 Vec3(vec4 v) { return vec3(v.x, v.y, v.z); }

// integer pair and triplet

inline int Flint(float x) { return (int) floor(x); }

struct int2 {
	int i1, i2;
	int2() { i1 = i2 = 0; }
	int2(int i1, int i2) : i1(i1), i2(i2) { }
	int2(vec2 v) : i1(Flint(v.x)), i2(Flint(v.y)) { }
	int &operator [] (int i) { return *(&i1+i); }
	const int operator [] (int i) const { return *(&i1+i); }
	bool operator == (const int2 &rhs) { return this->i1 == rhs.i1 && this->i2 == rhs.i2; }
	int2 operator + (const int2 &v) const { return int2(i1+v.i1, i2+v.i2); }
	int2 operator - (const int2 &v) const { return int2(i1-v.i1, i2-v.i2); }
};

struct int3 {
	int i1, i2, i3;
	int3() { i1 = i2 = i3 = 0; }
	int3(int *i) : i1(i[0]), i2(i[1]), i3(i[2]) { }
	int3(int i1, int i2, int i3) : i1(i1), i2(i2), i3(i3) { }
	int3(vec3 v) : i1(Flint(v.x)), i2(Flint(v.y)), i3(Flint(v.z)) { }
	int &operator [] (int i) { return *(&i1+i); }
	const int operator [] (int i) const { return *(&i1+i); }
	bool operator == (const int3 &rhs) { return this->i1 == rhs.i1 && this->i2 == rhs.i2 && this->i3 == rhs.i3; }
	int3 operator + (const int3 &v) const { return int3(i1+v.i1, i2+v.i2, i3+v.i3); }
	int3 operator - (const int3 &v) const { return int3(i1-v.i1, i2-v.i2, i3-v.i3); }
};

struct int4 {
	int i1, i2, i3, i4;
	int4() { i1 = i2 = i3 = i4 = 0; }
	int4(int *i) : i1(i[0]), i2(i[1]), i3(i[2]), i4(i[3]) { }
	int4(int i1, int i2, int i3, int i4) : i1(i1), i2(i2), i3(i3), i4(i4) { }
	int4(vec4 v) : i1(Flint(v.x)), i2(Flint(v.y)), i3(Flint(v.z)), i4(Flint(v.w)) { }
	int &operator [] (int i) { return *(&i1+i); }
	const int operator [] (int i) const { return *(&i1+i); }
	bool operator == (const int4& rhs) { return this->i1 == rhs.i1 && this->i2 == rhs.i2 && this->i3 == rhs.i3 && this->i4 == rhs.i4; }
};

// 3x3 matrix representation

class mat3 {
public:
	vec3 row[3];
	//  constructors
	mat3(float diag = 1) { row[0].x = row[1].y = row[2].z = diag; }
	mat3(const vec3 &r0, const vec3 &r1, const vec3 &r2) { row[0] = r0; row[1] = r1; row[2] = r2; }
	mat3(const mat3 &m) { for (int i = 0; i < 3; i++) row[i] = m.row[i]; }
	mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
		row[0] = vec3(a, b, c);
		row[1] = vec3(d, e, f);
		row[2] = vec3(g, h, i);
	}
	// access
	vec3 &operator [] (int i) { return row[i]; }
	const vec3 &operator [] (int i) const { return row[i]; }
	operator const float *() const { return static_cast<const float*>(&row[0].x); }
	// methods
	mat3 operator * (float s) const { return mat3(s*row[0], s*row[1], s*row[2]); }
	friend mat3 operator * (float s, const mat3 &m) { return m*s; }
	mat3 operator * (const mat3 &m) const {
		mat3 a(0);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					a[i][j] += row[i][k]*m[k][j];
		return a;
	}
	vec3 operator * (const vec3 &v) const { return vec3(dot(row[0], v), dot(row[1], v), dot(row[2], v)); }
};

inline mat3 Transpose(mat3 m) {
	mat3 r;
	r = mat3(vec3(m[0][0], m[1][0], m[2][0]),
			 vec3(m[0][1], m[1][1], m[2][1]),
			 vec3(m[0][2], m[1][2], m[2][2]));
	return r;
}

inline mat3 TransposeInverseMatrix3x3(mat3 m) {
	// from https://stackoverflow.com/questions/983999/simple-3x3-matrix-inverse-code-c/18504573#18504573
	float det = +m[0][0]*(m[1][1]*m[2][2]-m[2][1]*m[1][2])
	            -m[0][1]*(m[1][0]*m[2][2]-m[1][2]*m[2][0])
	            +m[0][2]*(m[1][0]*m[2][1]-m[1][1]*m[2][0]);
	float invdet = 1.f/det;
	mat3 r;
	r[0][0] =  (m[1][1]*m[2][2]-m[2][1]*m[1][2])*invdet;
	r[1][0] = -(m[0][1]*m[2][2]-m[0][2]*m[2][1])*invdet;
	r[2][0] =  (m[0][1]*m[1][2]-m[0][2]*m[1][1])*invdet;
	r[0][1] = -(m[1][0]*m[2][2]-m[1][2]*m[2][0])*invdet;
	r[1][1] =  (m[0][0]*m[2][2]-m[0][2]*m[2][0])*invdet;
	r[2][1] = -(m[0][0]*m[1][2]-m[1][0]*m[0][2])*invdet;
	r[0][2] =  (m[1][0]*m[2][1]-m[2][0]*m[1][1])*invdet;
	r[1][2] = -(m[0][0]*m[2][1]-m[2][0]*m[0][1])*invdet;
	r[2][2] =  (m[0][0]*m[1][1]-m[1][0]*m[0][1])*invdet;
	return r;
}

inline mat3 Adjoint3x3(mat3 in) {
	mat3 out;
	out[0][0] =   in[1][1]*in[2][2]-in[1][2]*in[2][1];
	out[1][0] = -(in[1][0]*in[2][2]-in[1][2]*in[2][0]);
	out[2][0] =   in[1][0]*in[2][1]-in[1][1]*in[2][0];
	out[0][1] = -(in[0][1]*in[2][2]-in[0][2]*in[2][1]);
	out[1][1] =   in[0][0]*in[2][2]-in[0][2]*in[2][0];
	out[2][1] = -(in[0][0]*in[2][1]-in[0][1]*in[2][0]);
	out[0][2] =   in[0][1]*in[1][2]-in[0][2]*in[1][1];
	out[1][2] = -(in[0][0]*in[1][2]-in[0][2]*in[1][0]);
	out[2][2] =   in[0][0]*in[1][1]-in[0][1]*in[1][0];
	return out;
};

inline bool InvertMatrix3x3(mat3 in, mat3 &out) {
	out = Adjoint3x3(in);
	float det = out[0][0]*in[0][0]+out[0][1]*in[1][0]+out[0][2]*in[2][0];
	if (det < FLT_EPSILON && det > -FLT_EPSILON)
		return false;
	float di = 1.f/det;
	out[0][0] = di*out[0][0];
	out[0][1] = di*out[0][1];
	out[0][2] = di*out[0][2];
	out[1][0] = di*out[1][0];
	out[1][1] = di*out[1][1];
	out[1][2] = di*out[1][2];
	out[2][0] = di*out[2][0];
	out[2][1] = di*out[2][1];
	out[2][2] = di*out[2][2];
	return true;
};

inline mat3 Inverse(mat3 m) {
	mat3 inv;
	InvertMatrix3x3(m, inv);
	return inv;
}

// 4x4 matrix

// representation
//     mat4 m;                  // defaults to identity
//     vec4 v0, v1, v2, v3;
//     mat4 m(v0, v1, v2, v3);  // four rows
//     mat4 m2(m);              // copy of m
// access
//     vec4 &row0 = m[0];
//     float f = m[i][j];
// operations
//     mat4 mm = m1*m2;         // matrix times matrix
//     mat4 sm = s*m1;          // matrix times scalar
//     vec4 xv = m*v;           // matrix times vector
// initializations
//     Scale, Translate, RotateX, RotateY, RotateZ
//     Orthographic, Perspective
//     LookAt, Transpose

class mat4 {
public:
	vec4 row[4];
	//  constructors
	mat4(float diag = 1) {
		row[0].x = row[1].y = row[2].z = row[3].w = diag;
	}
	mat4(const vec4 &r0, const vec4 &r1, const vec4 &r2, const vec4 &r3 = {0,0,0,1}) {
		row[0] = r0; row[1] = r1; row[2] = r2; row[3] = r3;
	}
	mat4(const mat4 &m) {
		for (int i = 0; i < 4; i++)
			row[i] = m.row[i];
	}
	mat4(const mat3 &m) {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				row[i][j] = m[i][j];
		row[3][3] = 1;
	}
	mat4(float a, float b, float c, float d, float e, float f, float g, float h,
		 float i, float j, float k, float l, float m, float n, float o, float p) {
			row[0] = vec4(a, b, c, d);
			row[1] = vec4(e, f, g, h);
			row[2] = vec4(i, j, k, l);
			row[3] = vec4(m, n, o, p);
	}
	// access
	vec4 &operator [] (int i) { return row[i]; }
	const vec4 &operator [] (int i) const { return row[i]; }
	operator const float *() const { return static_cast<const float*>(&row[0].x); }
	// methods
	mat4 operator * (float s) const { return mat4(s*row[0], s*row[1], s*row[2], s*row[3]); }
	friend mat4 operator * (float s, const mat4 &m) { return m*s; }
	mat4 operator * (const mat4 &m) const {
		mat4 a(0);
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				for (int k = 0; k < 4; k++)
					a[i][j] += row[i][k]*m[k][j];
		return a;
	}
	vec4 operator * (const vec4 &v) const { return vec4(dot(row[0], v), dot(row[1], v), dot(row[2], v), dot(row[3], v)); }
};

inline mat4 Scale(float x, float y, float z) {
	mat4 c;
	c[0][0] = x;
	c[1][1] = y;
	c[2][2] = z;
	return c;
}

inline mat4 Scale(vec3 s) { return Scale(s.x, s.y, s.z); }
inline mat4 Scale(float f) { return Scale(f, f, f); }

inline mat4 Translate(float x, float y, float z) {
	return mat4(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1);
}

inline mat4 Translate(vec3 t) { return Translate(t.x, t.y, t.z); }

// arguments to RotateX/Y/Z are in degrees
static float DegreesToRadians = 3.14159265358f/180.f;

inline mat4 RotateX(float theta) {
	float angle = DegreesToRadians*theta;
	mat4 c;
	c[2][2] = c[1][1] = cos(angle);
	c[2][1] = sin(angle);
	c[1][2] = -c[2][1];
	return c;
}

inline mat4 RotateY(float theta) {
	float angle = DegreesToRadians*theta;
	mat4 c;
	c[2][2] = c[0][0] = cos(angle);
	c[0][2] = sin(angle);
	c[2][0] = -c[0][2];
	return c;
}

inline mat4 RotateZ(float theta) {
	float angle = DegreesToRadians*theta;
	mat4 c;
	c[0][0] = c[1][1] = cos(angle);
	c[1][0] = sin(angle);
	c[0][1] = -c[1][0];
	return c;
}

inline mat4 Orthographic(float left, float right, float bottom, float top, float zNear = -1, float zFar = 1) {
	mat4 c;
	c[0][0] = 2.f/(right-left);
	c[1][1] = 2.f/(top-bottom);
	c[2][2] = 2.f/(zNear-zFar);
	c[3][3] = 1.f;
	c[0][3] = -(right+left)/(right-left);
	c[1][3] = -(top+bottom)/(top-bottom);
	c[2][3] = -(zFar+zNear)/(zFar-zNear);
	return c;
}

inline mat4 Perspective(float verticalFOV, float aspectRatio, float zNear, float zFar) {
	// convert view frustum to +/-1 perspective/clip space
	// zNear and zFar are positive distances (despite camera facing -z axis)
	// view frustum defined by verticalFOV (top, bottom), aspectRatio (left, right) and near, far
	// -1/+1 in perspective z defaults to full depth buffer
	float t = tan(verticalFOV*DegreesToRadians/2.f);
	float fnDif = zFar-zNear;
	mat4 m(0);
	m[0][0] = 1.f/(aspectRatio*t);
	m[1][1] = 1.f/t;
	m[2][2] = -(zFar+zNear)/fnDif;
	m[2][3] = -2.f*zFar*zNear/fnDif;
	m[3][2] = -1.f;
	return m;
}

inline mat4 LookTowards(vec3 eye, vec3 lookV, vec3 up) {
	// camera view matrix transforms standard coordinate system (origin at (0,0,0), x-axis to right) to arbitrary
	// scene coordinate system (ie, (0,0,0) transforms to origin of new system, (1,0,0) transforms to new x-axis) 
	// LookAt is inverse: it must transform arbitrary x-axis to (1,0,0) and arbitrary origin to (0,0,0)
	// if rotation is pure (no scale), its inverse is simply its transpose
	// the translation terms are projections of arbitrary origin onto arbitrary axes
	vec3 z = normalize(lookV);					// create 3 orthonormal axes
	vec3 x = normalize(cross(z, up)), y = cross(x, z);
	mat4 m = {{ x.x,  x.y,  x.z, -dot(x, eye)}, // upper 3x3 is transpose of pure rotation
		      { y.x,  y.y,  y.z, -dot(y, eye)}, // dot products move by eye projected onto new axes
		      {-z.x, -z.y, -z.z,  dot(z, eye)}, // negated so eye looks towards -z axis
			  { 0,    0,    0,    1}};
	return m;
}

inline mat4 LookAt(vec3 eye, vec3 lookat, vec3 up) { return LookTowards(eye, lookat-eye, up); }

inline mat4 Transpose(mat4 m) {
	return mat4(vec4(m[0][0], m[1][0], m[2][0], m[3][0]),
				vec4(m[0][1], m[1][1], m[2][1], m[3][1]),
				vec4(m[0][2], m[1][2], m[2][2], m[3][2]),
				vec4(m[0][3], m[1][3], m[2][3], m[3][3]));
}

inline mat4 ReferenceFrame(vec3 x, vec3 y, vec3 z, vec3 o) {
	return Transpose(mat4(vec4(x, 0), vec4(y, 0), vec4(z, 0), vec4(o, 1)));
}

inline bool InvertMatrix4x4(const float *m, float *out) {
	// from https://gamesxmath.tumblr.com/post/86495837013/inverting-a-4x4-matrix-using-c-code-float
	class Helper {
	public:
		const float *m = NULL;
		float e(int a, int b, const float *m) {
			return m[ (b%4)*4 + a%4 ];
		}
		float invf(int i,int j, const float *m) {
			int o = 2+(j-i);
			i += 4+o;
			j += 4-o;
			float inv =
				 + e(i+1,j-1,m)*e(i+0,j+0,m)*e(i-1,j+1,m)
				 + e(i+1,j+1,m)*e(i+0,j-1,m)*e(i-1,j+0,m)
				 + e(i-1,j-1,m)*e(i+1,j+0,m)*e(i+0,j+1,m)
				 - e(i-1,j-1,m)*e(i+0,j+0,m)*e(i+1,j+1,m)
				 - e(i-1,j+1,m)*e(i+0,j-1,m)*e(i+1,j+0,m)
				 - e(i+1,j-1,m)*e(i-1,j+0,m)*e(i+0,j+1,m);
			return (o%2)? inv : -inv;
			#undef e
		}
		bool invert(float *out) {
			float inv[16];
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					inv[j*4+i] = invf(i,j,m);
			double D = 0;
			for (int k = 0; k < 4; k++)
				D += (double) m[k]*inv[k*4];
			if (D == 0)
				return false;
			D = 1.0/D;
			for (int i = 0; i < 16; i++)
				out[i] = (float) ((double) inv[i]*D);
			return true;
		}
		Helper(const float *m = NULL) : m(m) { }
	} h(m);
	return h.invert(out);
}

inline mat4 Inverse(mat4 m) {
	mat4 inv;
	InvertMatrix4x4(&m[0][0], &inv[0][0]);
	return inv;
}

// quaternions

const int X = 0, Y = 1, Z = 2;

class Quaternion {
public:
	#define _PI 3.141592f
	float x = 0, y = 0, z = 0, w = 0;
	Quaternion() { };
	Quaternion(vec3 axis, float radAng) {
		float c = cos(radAng/2), s = sin(radAng/2);
		vec3 a = normalize(axis);
		x = s*a.x; y = s*a.y; z = s*a.z; w = c;
	}
	Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { };
	Quaternion(mat3 mat) { // presumes rot is pure rotation matrix (no scale)
		float s, tr = mat[X][X]+mat[Y][Y]+mat[Z][Z];
		if (tr >= 0) {
			w = (float) sqrt(.25f*(tr+1));
			s = .25f/w;
			x = (mat[Z][Y] - mat[Y][Z]) * s;
			y = (mat[X][Z] - mat[Z][X]) * s;
			z = (mat[Y][X] - mat[X][Y]) * s;
		}
		else {
		#define caseMacro(i, j, k, I, J, K)                             \
			case I:                                                     \
				i = sqrt(.25f*(mat[I][I] - mat[J][J] - mat[K][K] + 1)); \
				s = .25f/i;                                             \
				j = (mat[I][J] + mat[J][I]) * s;                        \
				k = (mat[K][I] + mat[I][K]) * s;                        \
				w = (mat[K][J] - mat[J][K]) * s;                        \
				break
			switch ((mat[X][X] >= mat[Y][Y])?
				   ((mat[X][X] >= mat[Z][Z])? X : Z) :
				   ((mat[Y][Y] >= mat[Z][Z])? Y : Z)) {
						caseMacro(x, y, z, X, Y, Z);
						caseMacro(y, z, x, Y, Z, X);
						caseMacro(z, x, y, Z, X, Y);
			}
		}
	}
	Quaternion(mat4 m) {
		mat3 t = mat3(vec3(m[0][0], m[1][0], m[2][0]), vec3(m[0][1], m[1][1], m[2][1]), vec3(m[0][2], m[1][2], m[2][2]));
		// the following transpose for left-handed coord sys
		// mat3 t = mat3(vec3(m[0][0], m[0][1], m[0][2]), vec3(m[1][0], m[1][1], m[1][2]), vec3(m[2][0], m[2][1], m[2][2]));
		// remove scaling if any *** only if uniform scale! (differential scale must be treated differently)
		float xlen = length(vec3(m[0][0], m[1][0], m[2][0])); // x column scale
		float ylen = length(vec3(m[0][1], m[1][1], m[2][1]));
		float zlen = length(vec3(m[0][2], m[1][2], m[2][2]));
		// *** should test here that xlen, ylen, zlen are same
		for (int i = 0; i < 3; i++) t[i][0] /= xlen;
		for (int i = 0; i < 3; i++) t[i][1] /= ylen;
		for (int i = 0; i < 3; i++) t[i][2] /= zlen;
		*this = Quaternion(t);
	}
	Quaternion(const Quaternion &a) { x = a.x; y = a.y; z = a.z; w = a.w; }
	Quaternion& operator = (const Quaternion &a) { x = a.x; y = a.y; z = a.z; w = a.w; return *this; }
	Quaternion operator + (const Quaternion &q) const { return Quaternion(x+q.x, y+q.y, z+q.z, w+q.w); }
	Quaternion operator * (float s) const { return Quaternion(s*x, s*y, s*z, s*w); }
	Quaternion operator * (const Quaternion &q) const {
		float xx =  x*q.w+y*q.z-z*q.y+w*q.x;
		float yy = -x*q.z+y*q.w+z*q.x+w*q.y;
		float zz =  x*q.y-y*q.x+z*q.w+w*q.z;
		float ww = -x*q.x-y*q.y-z*q.z+w*q.w;
		return Quaternion(xx, yy, zz, ww);
	}
	float Norm() { return x*x+y*y+z*z+w*w; }
	mat3 Get3x3() {
		float norm = Norm();
		if (fabs(norm) < FLT_EPSILON)
			return mat3(vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1));
		float s = 2/norm;
		float xs = x*s,  ys = y*s,  zs = z*s;
		float wx = w*xs, wy = w*ys, wz = w*zs;
		float xx = x*xs, xy = x*ys, xz = x*zs;
		float yy = y*ys, yz = y*zs, zz = z*zs;
		return mat3(
			vec3(1 - (yy + zz), xy + wz,       xz - wy),
			vec3(xy - wz,       1 - (xx + zz), yz + wx),
			vec3(xz + wy,       yz - wx,       1 - (xx + yy)));
	}
	mat4 GetMatrix() {
		mat3 m3 = Get3x3();
		return mat4(m3);
	}
	float Dot(Quaternion &qL, Quaternion &qR) {
		return qL.x*qR.x+qL.y*qR.y+qL.z*qR.z+qL.w*qR.w;
	}
	void Slerp(Quaternion &qu0, Quaternion &qu1, float t) {
		float qu0Part, qu1Part, epsilon = .00001f;
		float cosOmega = Dot(qu0, qu1);
		if ((1 + cosOmega) > epsilon) { // usual case
			if ((1 - cosOmega) > epsilon) { // usual case
				float omega = acos(cosOmega);
				float sinOmega = sin(omega);
				qu0Part = sin((1 - t)*omega)/sinOmega;
				qu1Part = sin(t*omega)/sinOmega;
			}
			else { // ends very close
				qu0Part = 1.0f - t;
				qu1Part = t;
			}
			Quaternion s1 = qu0*qu0Part, s2 = qu1*qu1Part; // s1 = Scale(qu0, qu0Part), s2 = Scale(qu1, qu1Part);
			*this = s1+s2; // Add(s1, s2);
		}
		else { // ends nearly opposite
			Quaternion qup(-qu0.y, qu0.x, -qu0.w, qu0.z);
			qu0Part = sin((0.5f - t)*_PI);
			qu1Part = sin(t*_PI);
			Quaternion s1 = qu0*qu0Part, s2 = qup*qu1Part;
			*this = s1+s2;
		}
	}
};

#endif // VEC_MAT_HDR
