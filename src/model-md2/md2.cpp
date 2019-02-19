//
//	md2.cpp - source file
//
//	David Henry - tfc_duke@hotmail.com
//


#include	<GL/glut.h>
#include	<fstream>

#include	"md2.h"
#include	"texture.h"




// precalculated normal vectors
vec3_t	CMD2Model::anorms[ NUMVERTEXNORMALS ] = {
#include	"anorms.h"
};

// precalculated dot product results
float	CMD2Model::anorms_dots[ SHADEDOT_QUANT ][256] = {
#include	"anormtab.h"
};


static float	*shadedots = CMD2Model::anorms_dots[0];
static vec3_t	lcolor;


/////////////////////////////////////////////////

vec3_t			g_lightcolor	= { 1.0, 1.0, 1.0 };
int				g_ambientlight	= 32;
float			g_shadelight	= 128;
float			g_angle			= 0.0;

/////////////////////////////////////////////////



// ----------------------------------------------
// constructor - reset all data.
// ----------------------------------------------

CMD2Model::CMD2Model( void )
{
	m_vertices		= 0;
	m_glcmds		= 0;
	m_lightnormals	= 0;

	num_frames		= 0;
	num_xyz			= 0;
	num_glcmds		= 0;

	m_texid			= 0;
	m_scale			= 1.0;

	SetAnim( 0 );
}



// ----------------------------------------------
// destructeur - free allocated memory.
// ----------------------------------------------

CMD2Model::~CMD2Model( void )
{
	delete [] m_vertices;
	delete [] m_glcmds;
	delete [] m_lightnormals;
}



// ----------------------------------------------
// LoadModel() - load model from file.
// ----------------------------------------------

bool CMD2Model::LoadModel( const char *filename )
{
	std::ifstream	file;			// file stream
	md2_t			header;			// md2 header
	char			*buffer;		// buffer storing frame data
	frame_t			*frame;			// temporary variable
	vec3_t			*ptrverts;		// pointer on m_vertices
	int				*ptrnormals;	// pointer on m_lightnormals


	// try to open filename
	file.open( filename, std::ios::in | std::ios::binary );

	if( file.fail() )
		return false;

	// read header file
	file.read( (char *)&header, sizeof( md2_t ) );


	/////////////////////////////////////////////
	//		verify that this is a MD2 file

	// check for the ident and the version number

	if( (header.ident != MD2_IDENT) && (header.version != MD2_VERSION) )
	{
		// this is not a MD2 model
		file.close();
		return false;
	}

	/////////////////////////////////////////////


	// initialize member variables
	num_frames	= header.num_frames;
	num_xyz		= header.num_xyz;
	num_glcmds	= header.num_glcmds;


	// allocate memory
	m_vertices		= new vec3_t[ num_xyz * num_frames ];
	m_glcmds		= new int[ num_glcmds ];
	m_lightnormals	= new int[ num_xyz * num_frames ];
	buffer			= new char[ num_frames * header.framesize ];


	/////////////////////////////////////////////
	//			reading file data

	// read frame data...
	file.seekg( header.ofs_frames, std::ios::beg );
	file.read( (char *)buffer, num_frames * header.framesize );

	// read opengl commands...
	file.seekg( header.ofs_glcmds, std::ios::beg );
	file.read( (char *)m_glcmds, num_glcmds * sizeof( int ) );

	/////////////////////////////////////////////


	// vertex array initialization
	for( int j = 0; j < num_frames; j++ )
	{
		// ajust pointers
		frame		= (frame_t *)&buffer[ header.framesize * j ];
		ptrverts	= &m_vertices[ num_xyz * j ];
		ptrnormals	= &m_lightnormals[ num_xyz * j ];

		for( int i = 0; i < num_xyz; i++ )
		{
			ptrverts[i][0] = (frame->verts[i].v[0] * frame->scale[0]) + frame->translate[0];
			ptrverts[i][1] = (frame->verts[i].v[1] * frame->scale[1]) + frame->translate[1];
			ptrverts[i][2] = (frame->verts[i].v[2] * frame->scale[2]) + frame->translate[2];

			ptrnormals[i] = frame->verts[i].lightnormalindex;
		}
	}


	// free buffer's memory
	delete [] buffer;

	// close the file and return
	file.close();
	return true;
}



// ----------------------------------------------
// LoadSkin() - load model texture.
// ----------------------------------------------

bool CMD2Model::LoadSkin( const char *filename )
{
	m_texid = LoadTexture( filename );

	return (m_texid != LoadTexture( "default" ));
}



// ----------------------------------------------
// DrawModel() - draw the model.
// ----------------------------------------------

void CMD2Model::DrawModel( float time )
{
	// animate. calculate current frame and next frame
	if( time > 0.0 )
		Animate( time );

	glPushMatrix();
		// rotate the model
		glRotatef( -90.0, 1.0, 0.0, 0.0 );
		glRotatef( -90.0, 0.0, 0.0, 1.0 );

		// render it on the screen
		RenderFrame();
	glPopMatrix();
}



// ----------------------------------------------
// Animate() - calculate the current frame, next
// frame and interpolation percent.
// ----------------------------------------------

void CMD2Model::Animate( float time )
{
	m_anim.curr_time = time;

	// calculate current and next frames
	if( m_anim.curr_time - m_anim.old_time > (1.0 / m_anim.fps) )
	{
		m_anim.curr_frame = m_anim.next_frame;
		m_anim.next_frame++;

		if( m_anim.next_frame > m_anim.endframe )
			m_anim.next_frame = m_anim.startframe;

		m_anim.old_time = m_anim.curr_time;
	}

	// prevent having a current/next frame greater
	// than the total number of frames...
	if( m_anim.curr_frame > (num_frames - 1) )
		m_anim.curr_frame = 0;

	if( m_anim.next_frame > (num_frames - 1) )
		m_anim.next_frame = 0;

	m_anim.interpol = m_anim.fps * (m_anim.curr_time - m_anim.old_time);
}



// ----------------------------------------------
// ProcessLighting() - process all lighting calculus.
// ----------------------------------------------

void CMD2Model::ProcessLighting( void )
{
	float lightvar = (float)((g_shadelight + g_ambientlight)/256.0);

	lcolor[0] = g_lightcolor[0] * lightvar;
	lcolor[1] = g_lightcolor[1] * lightvar;
	lcolor[2] = g_lightcolor[2] * lightvar;

	shadedots = anorms_dots[ ((int)(g_angle * (SHADEDOT_QUANT / 360.0))) & (SHADEDOT_QUANT - 1) ];
}



// ----------------------------------------------
// Interpolate() - interpolate and scale vertices
// from the current and the next frame.
// ----------------------------------------------

void CMD2Model::Interpolate( vec3_t *vertlist )
{
	vec3_t	*curr_v;	// pointeur to current frame vertices
	vec3_t	*next_v;	// pointeur to next frame vertices

	// create current frame and next frame's vertex list
	// from the whole vertex list
	curr_v = &m_vertices[ num_xyz * m_anim.curr_frame ];
	next_v = &m_vertices[ num_xyz * m_anim.next_frame ];

	// interpolate and scale vertices to avoid ugly animation
	for( int i = 0; i < num_xyz ; i++ )
	{
		vertlist[i][0] = (curr_v[i][0] + m_anim.interpol * (next_v[i][0] - curr_v[i][0])) * m_scale;
		vertlist[i][1] = (curr_v[i][1] + m_anim.interpol * (next_v[i][1] - curr_v[i][1])) * m_scale;
		vertlist[i][2] = (curr_v[i][2] + m_anim.interpol * (next_v[i][2] - curr_v[i][2])) * m_scale;
	}
}



// ----------------------------------------------
// RenderFrame() - draw the current model frame
// using OpenGL commands.
// ----------------------------------------------

void CMD2Model::RenderFrame( void )
{
	static vec3_t	vertlist[ MAX_MD2_VERTS ];	// interpolated vertices
	int				*ptricmds = m_glcmds;		// pointer on gl commands


	// reverse the orientation of front-facing
	// polygons because gl command list's triangles
	// have clockwise winding
	glPushAttrib( GL_POLYGON_BIT );
	glFrontFace( GL_CW );

	// enable backface culling
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );


	// process lighting
	ProcessLighting();

	// interpolate
	Interpolate( vertlist );

	// bind model's texture
	glBindTexture( GL_TEXTURE_2D, m_texid );


	// draw each triangle!
	while( int i = *(ptricmds++) )
	{
		if( i < 0 )
		{
			glBegin( GL_TRIANGLE_FAN );
			i = -i;
		}
		else
		{
			glBegin( GL_TRIANGLE_STRIP );
		}


		for( /* nothing */; i > 0; i--, ptricmds += 3 )
		{
			// ptricmds[0] : texture coordinate s
			// ptricmds[1] : texture coordinate t
			// ptricmds[2] : vertex index to render

			float l = shadedots[ m_lightnormals[ ptricmds[2] ] ];

			// set the lighting color
			glColor3f( l * lcolor[0], l * lcolor[1], l * lcolor[2] );

			// parse texture coordinates
			glTexCoord2f( ((float *)ptricmds)[0], ((float *)ptricmds)[1] );

			// parse triangle's normal (for the lighting)
			// >>> only needed if using OpenGL lighting
			glNormal3fv( anorms[ m_lightnormals[ ptricmds[2] ] ] );

			// draw the vertex
			glVertex3fv( vertlist[ ptricmds[2] ] );
		}

		glEnd();
	}

	glDisable( GL_CULL_FACE );
	glPopAttrib();
}



// ----------------------------------------------
// RenderFrame() - draw one frame of the model
// using gl commands.
// ----------------------------------------------

void CMD2Model::DrawFrame( int frame )
{
	// set new animation parameters...
	m_anim.startframe	= frame;
	m_anim.endframe		= frame;
	m_anim.next_frame	= frame;
	m_anim.fps			= 1;
	m_anim.type			= -1;

	// draw the model
	DrawModel( 1.0 );
}



// ----------------------------------------------
// initialize the 21 MD2 model animations.
// ----------------------------------------------

anim_t CMD2Model::animlist[ 21 ] = 
{
	// first, last, fps

	{   0,  39,  9 },	// STAND
	{  40,  45, 10 },	// RUN
	{  46,  53, 10 },	// ATTACK
	{  54,  57,  7 },	// PAIN_A
	{  58,  61,  7 },	// PAIN_B
	{  62,  65,  7 },	// PAIN_C
	{  66,  71,  7 },	// JUMP
	{  72,  83,  7 },	// FLIP
	{  84,  94,  7 },	// SALUTE
	{  95, 111, 10 },	// FALLBACK
	{ 112, 122,  7 },	// WAVE
	{ 123, 134,  6 },	// POINT
	{ 135, 153, 10 },	// CROUCH_STAND
	{ 154, 159,  7 },	// CROUCH_WALK
	{ 160, 168, 10 },	// CROUCH_ATTACK
	{ 196, 172,  7 },	// CROUCH_PAIN
	{ 173, 177,  5 },	// CROUCH_DEATH
	{ 178, 183,  7 },	// DEATH_FALLBACK
	{ 184, 189,  7 },	// DEATH_FALLFORWARD
	{ 190, 197,  7 },	// DEATH_FALLBACKSLOW
	{ 198, 198,  5 },	// BOOM
};



// ----------------------------------------------
// SetAnim() - initialize m_anim from the specified
// animation.
// ----------------------------------------------

void CMD2Model::SetAnim( int type )
{
	if( (type < 0) || (type > MAX_ANIMATIONS) )
		type = 0;

	m_anim.startframe	= animlist[ type ].first_frame;
	m_anim.endframe		= animlist[ type ].last_frame;
	m_anim.next_frame	= animlist[ type ].first_frame + 1;
	m_anim.fps			= animlist[ type ].fps;
	m_anim.type			= type;
}
