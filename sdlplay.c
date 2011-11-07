#include <stdio.h>
#include <SDL.h>

#include "pmdmini.h"

#include "pmdwin/pmdwinimport.h"

int audio_on = 0;

//
// PCM definitions ( BLOCK = samples )
// 

#define PCM_BLOCK 512
#define PCM_BYTE_PER_SAMPLE 2
#define PCM_CH  2


//
// buffer size definitions
//

#define BUF_BLKSIZE PCM_BLOCK
#define BUF_BLKNUM 16
#define BUF_LEN ( BUF_BLKSIZE * PCM_CH * BUF_BLKNUM )


//
// audio buffering
//

int buf_wpos = 0;
int buf_ppos = 0;

short buffer[ BUF_LEN ];

void audio_callback( void *param , Uint8 *data , int len )
{
	int i,j;
	
	short *pcm = (short *)data;

	if ( !audio_on )
	{
		memset( data , 0 , len );
		return;
	}
	
	for( i = 0; i < len / 2; i++ )
	{
		pcm[ i ] = buffer[ buf_ppos++ ];
		if ( buf_ppos >= BUF_LEN )
				buf_ppos = 0;
	}
}

//
// audio hardware functions
//

int init_audio(void)
{
	SDL_AudioSpec af;

	if ( SDL_Init( SDL_INIT_AUDIO ) )
	{
		printf("Failed to Initialize!!\n");
		return 1;
	}
	
	af.freq = 44100;
	af.format = AUDIO_S16;
	af.channels = 2;
	af.samples = 512;
	af.callback = audio_callback;
	af.userdata = NULL;

	if (SDL_OpenAudio(&af,NULL) < 0)
	{
		printf("Audio Error!!\n");
		return 1;
	}
	
	memset(buffer,0,sizeof(buffer));
	
	SDL_PauseAudio(0);
	return 0;
}

void free_audio(void)
{
	SDL_CloseAudio();
}


void player_screen( void )
{
	int i,n;
	int notes[32];
	
	n = pmd_get_tracks ( );
	
	pmd_get_current_notes( notes , n );
	
	for ( i = 0; i < n; i ++ )
	{
		printf("%02x " , ( notes[i] & 0xff ) );
	}
	printf(" ");
		
}



//
// audio renderer
//
void player_loop( int len )
{

	int i,j;
	
	int total;
	int sec,old_sec;
	int sec_sample;
	int freq;
	
	freq = 44100;
	old_sec = total = sec = sec_sample = 0;
		
	do
	{
		//
		// Wait empty block
		//
		
		while( buf_wpos >= buf_ppos &&
			  buf_wpos <  buf_ppos + ( PCM_BLOCK * PCM_CH ) )
		{
			SDL_Delay(10);
		}

		pmd_renderer ( buffer + buf_wpos, PCM_BLOCK );
		
		buf_wpos += PCM_BLOCK * PCM_CH;
		if (buf_wpos >= BUF_LEN)
				buf_wpos = 0;
		
		total += PCM_BLOCK;
		sec_sample += PCM_BLOCK;
		
		while ( sec_sample >= freq )
		{
			sec_sample -= freq;
			sec++;
		}
		
		if ( sec != old_sec )
		{
		
			old_sec = sec;
		}
		
		player_screen();
		printf("Time : %02d:%02d / %02d:%02d\r\r",
			sec / 60 , sec % 60 , len / 60,len % 60);
		fflush(stdout);
				

	} while(sec < len);

}

//
// path splitter
//

int split_dir( const char *file , char *dir )
{
	char *p;
	int len = 0;
	
	p = strrchr( file , '/' );

	if ( p )
	{
		len = (int)( p - file );
		strncpy ( dir , file , len );
	}
	dir[ len ] = 0;
	
	return len;
}

//
// entry point
//

int main ( int argc, char *argv[] )
{
	FILE *fp;
	
	printf( "PMDPLAY on SDL Version 2011-10-21\n" );
	
	if ( argc < 2 )
	{
		printf("Usage pmdplay <file>\n");
		return 1;
	}
	
	if ( init_audio() )
	{
		return 1;
	}
	
	pmd_init();
	
	pmd_play( argv[1] );
	audio_on = 1;
	
	player_loop( pmd_length_sec() );
	
	pmd_stop();
	
	free_audio();

	return 0;
}
