//
//	md2.h - header file
//
//	David Henry - tfc_duke@hotmail.com
//


#ifndef		__MD2_H
#define		__MD2_H



// number of precalculated normals
#define NUMVERTEXNORMALS		162

// precalculated normal vectors
#define SHADEDOT_QUANT			16

// magic number "IDP2" or 844121161
#define MD2_IDENT				(('2'<<24) + ('P'<<16) + ('D'<<8) + 'I')

// model version
#define	MD2_VERSION				8

// maximum number of vertices for a MD2 model
#define MAX_MD2_VERTS			2048



typedef float vec3_t[3];



// md2 header
typedef struct
{
	int		ident;				// magic number. must be equal to "IPD2"
	int		version;			// md2 version. must be equal to 8

	int		skinwidth;			// width of the texture
	int		skinheight;			// height of the texture
	int		framesize;			// size of one frame in bytes

	int		num_skins;			// number of textures
	int		num_xyz;			// number of vertices
	int		num_st;				// number of texture coordinates
	int		num_tris;			// number of triangles
	int		num_glcmds;			// number of opengl commands
	int		num_frames;			// total number of frames

	int		ofs_skins;			// offset to skin names (64 bytes each)
	int		ofs_st;				// offset to s-t texture coordinates
	int		ofs_tris;			// offset to triangles
	int		ofs_frames;			// offset to frame data
	int		ofs_glcmds;			// offset to opengl commands
	int		ofs_end;			// offset to the end of file

} md2_t;



// vertex
typedef struct
{
	unsigned char	v[3];				// compressed vertex' (x, y, z) coordinates
	unsigned char	lightnormalindex;	// index to a normal vector for the lighting

} vertex_t;



// frame
typedef struct
{
	float		scale[3];		// scale values
	float		translate[3];	// translation vector
	char		name[16];		// frame name
	vertex_t	verts[1];		// first vertex of this frame

} frame_t;



// animation
typedef struct
{
	int		first_frame;			// first frame of the animation
	int		last_frame;				// number of frames
	int		fps;					// number of frames per second

} anim_t;



// status animation
typedef struct
{
	int		startframe;				// first frame
	int		endframe;				// last frame
	int		fps;					// frame per second for this animation

	float	curr_time;				// current time
	float	old_time;				// old time
	float	interpol;				// percent of interpolation

	int		type;					// animation type

	int		curr_frame;				// current frame
	int		next_frame;				// next frame

} animState_t;



// animation list
typedef enum {
	STAND,
	RUN,
	ATTACK,
	PAIN_A,
	PAIN_B,
	PAIN_C,
	JUMP,
	FLIP,
	SALUTE,
	FALLBACK,
	WAVE,
//	POINT,
	CROUCH_STAND,
	CROUCH_WALK,
	CROUCH_ATTACK,
	CROUCH_PAIN,
	CROUCH_DEATH, 
	DEATH_FALLBACK,
	DEATH_FALLFORWARD,
	DEATH_FALLBACKSLOW,
	BOOM,

	MAX_ANIMATIONS

} animType_t;



// ==============================================
// CMD2Model - MD2 model class object.
// ==============================================

class CMD2Model
{
public:
	// constructor/destructor
	CMD2Model( void );
	~CMD2Model( void );


	// functions
	bool	LoadModel( const char *filename );
	bool	LoadSkin( const char *filename );

	void	DrawModel( float time );
	void	DrawFrame( int frame );

	void	SetAnim( int type );
	void	ScaleModel( float s ) { m_scale = s; }


private:
	void	Animate( float time );
	void	ProcessLighting( void );
	void	Interpolate( vec3_t *vertlist );
	void	RenderFrame( void );


public:
	// member variables
	static vec3_t	anorms[ NUMVERTEXNORMALS ];
	static float	anorms_dots[ SHADEDOT_QUANT ][256];

	static anim_t	animlist[21];		// animation list


private:
	int				num_frames;			// number of frames
	int				num_xyz;			// number of vertices
	int				num_glcmds;			// number of opengl commands

	vec3_t			*m_vertices;		// vertex array
	int				*m_glcmds;			// opengl command array
	int				*m_lightnormals;	// normal index array

	unsigned int	m_texid;			// texture id
	animState_t		m_anim;				// animation
	float			m_scale;			// scale value

};


#endif	// __MD2_H
