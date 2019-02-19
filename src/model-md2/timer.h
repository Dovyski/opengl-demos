//
//	timer.h - header file
//
//	David Henry - tfc_duke@hotmail.com
//


#ifndef		__TIMER_H
#define		__TIMER_H



// ==============================================
// CTimer - timer.
// ==============================================

class CTimer
{
protected:
	// constructor/destructor
	CTimer( void )	{ Initialize(); }
	~CTimer( void )	{ }


public:
	// singleton functions
	static CTimer	*GetInstance( void )
	{
		if( m_singleton == 0 )
			m_singleton = new CTimer;

		return ((CTimer *)m_singleton);
	}


	static void		FreeInstance( void )
	{
		if( m_singleton != 0 )
		{
			delete m_singleton;
			m_singleton = 0;
		}
	}


	// functions
	void			Initialize( void )		{ m_currentTime = GetTimeMSec(); m_lastTime = 0; }
	void			Update( void )			{ m_lastTime = m_currentTime; m_currentTime = GetTimeMSec(); }

	unsigned long	GetTimeMSec( void )		{ return glutGet( GLUT_ELAPSED_TIME ); }
	unsigned long	GetTime( void )			{ return m_currentTime; }
	float			GetFps( void )			{ return ((float)1000.0 / (float)(m_currentTime - m_lastTime)); }


private:
	// members variables
	unsigned long	m_currentTime;
	unsigned long	m_lastTime;

	// singleton
	static CTimer	*m_singleton;

};



// initialize singleton
CTimer *CTimer::m_singleton = 0;


#endif	// __TIMER_H
