#include <stdio.h>
#include <time.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_trig.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>

#include "soltrack.h"

#define DEBUG_PRINT 1

#define V_DIM 3 // Dimension of all vectors
// Which element is where in a vector
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2
// Custom errors
#define SOL_DOMAIN_ERROR 1

/**
 * Conventions:
 * The prefix uv_ stands for unit vector
 * The prefix rm_ stands for rotation matrix
 * The prefix rad_ stands for an angle in radians
 * The prefix deg_ stands for an angle in degrees
 */

//------------------------- STATIC GLOBALS ------------------------

// Is set to 1 if init was called successfully
static char initialized = 0;

// The earths axial tilt in radians
static const double rad_ax_tilt = (23.44 / 180.0) * M_PI;

/**
 * The following vector is defined in the space with coordinates
 * that turn with the earths rotation. Greenwich lies in the XZ-plane
 * in positive direction, the north pole is on the Z-axis in positive
 * direction.
 * The vector is the unit vector orthogonal to the earths surface
 * at the coordinates given through lat and long in the function:
 * soltrack_init()
 */
static gsl_vector *uv_orth_w_spin = NULL;

/**
 * The following matrix is the rotation matrix which turns the earths
 * axis by 23.44 degrees.
 * Initialisation in soltrack_init()
 */
static gsl_matrix *rm_ax_tilt = NULL;

//---------------------------- FUNCTIONS --------------------------

/* Define short writing forms for gsl_sf_cogsl_sf_sinus and gsl_sf_sinus
double (*gsl_sf_sin)(double);
gsl_sf_sin = gsl_sf_gsl_sf_sin;
double (*gsl_sf_cos)(double);
gsl_sf_cos = gsl_sf_gsl_sf_cos;
*/

/**
 * Checks if an angle is in the domain [-180°, 180°]
 * 
 * @argument deg is an angle in degrees
 * @return 0 if deg is in range
 */
static int check_long(const double deg)
{
	return (-180.0 <= deg && deg < 180.0);
}

/**
 * Checks if an angle is in the domain [-90°, 90°]
 * 
 * @argument deg is an angle in degrees
 * @return 0 if deg is in range
 */
static int check_lat(const double deg)
{
	return (-90.0 <= deg && deg <= 90);
}

static inline double deg_to_rad(double deg)
{
	return M_PI * (deg / 180.0);
}

int soltrack_init(double deg_lat, double deg_long)
{
	// Check domain
	if (!(check_lat(deg_lat) && check_long(deg_long))) {
		return SOL_DOMAIN_ERROR;
	}
	// Calculate latitude and longitude in radians
	double rad_lat = deg_to_rad(deg_lat);
	double rad_long = deg_to_rad(deg_long);
	
	#if DEBUG_PRINT == 1
	printf("Latitude: %frad\n", rad_lat);
	printf("Longitude: %frad\n\n", rad_long);
	#endif
	
	// Create a 3-dimensional vector
	uv_orth_w_spin = gsl_vector_alloc(V_DIM);
	gsl_vector_set(uv_orth_w_spin, X_AXIS, \
		gsl_sf_cos(rad_long) * gsl_sf_cos(rad_lat));
	gsl_vector_set(uv_orth_w_spin, Y_AXIS, \
		gsl_sf_sin(rad_long) * gsl_sf_cos(rad_lat));
	gsl_vector_set(uv_orth_w_spin, Z_AXIS, gsl_sf_sin(rad_lat));
	// Create the rotation matrix for axial tilt of the earth
	rm_ax_tilt = gsl_matrix_calloc(V_DIM, V_DIM); // Initialize 0
	// X-Axis
	gsl_matrix_set(rm_ax_tilt, X_AXIS, X_AXIS, gsl_sf_cos(rad_ax_tilt));
	gsl_matrix_set(rm_ax_tilt, X_AXIS, Z_AXIS, -gsl_sf_sin(rad_ax_tilt));
	// Y-Axis (no rotation)
	gsl_matrix_set(rm_ax_tilt, Y_AXIS, Y_AXIS, 1.0);
	// Z-Axis
	gsl_matrix_set(rm_ax_tilt, Z_AXIS, X_AXIS, gsl_sf_sin(rad_ax_tilt));
	gsl_matrix_set(rm_ax_tilt, Z_AXIS, Z_AXIS, gsl_sf_cos(rad_ax_tilt));
	
	// Initialisation complete
	initialized = 1;	
	return 0;
}

void print_tilt()
{
	if (!initialized) return;
	gsl_matrix_fprintf(stdout, rm_ax_tilt, "%f");
}

void print_orth_with_spin()
{
	if (!initialized) return;
	gsl_vector_fprintf(stdout, uv_orth_w_spin, "%f");
}
