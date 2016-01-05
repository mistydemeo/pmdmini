/**
 * \file pmdmini.h
 * \author BouKiCHi
 * \author Misty De Meo
 * \date 4 January 2016
 * \brief Core header for pmdmini.
 *
 * Note that the current version of pmdmini only allows a *single* file to be open in a given process.
 * This may be alleviated in the future, but in the current version it is not possible to process multiple files simultaneously without operating in separate processes.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __PMDMINI_H__
#define __PMDMINI_H__


/**
 * \brief Initializes the library.
 *        This should be called before doing anything else.
 */
void pmd_init(void);
/**
 * \brief Sets the frequency at which raw PCM data is generated.
 *
 * \param freq a frequency in Hz, for example 44100.
 */
void pmd_setrate( int freq );
/**
 * \brief Determines whether the provided path is to a valid PMD song.
 *
 * \param file the fully-qualified path to a file on disk.
 * \return 0 if file does not exist or is not valid, 1 otherwise.
 */
int pmd_is_pmd( const char *file );
/**
 * \brief Initiates playback for the specified file.
 *
 * \param file the fully-qualified path to a file on disk.
 * \param dir a fully-qualified path on disk in which PDX samples are located.
 * \return 1 if the file cannot be opened, 0 otherwise.
 */
int pmd_play ( const char *file , char *pcmdir );
/**
 * \brief Returns the length, in seconds, of the currently-open file.
 *
 * \param file the fully-qualified path to a file on disk.
 * \return the length of the file, in whole seconds.
 */
int pmd_length_sec ( void );
/**
 * \brief Returns the length, in seconds, of only the defined loop within the currently-open file.
 *
 * \param file the fully-qualified path to a file on disk.
 * \return the length of the file, in whole seconds.
 */
int pmd_loop_sec ( void );
/**
 * \brief Renders `len` bytes of the song into `buf`, and advances the internal song position.
 *
 * \param buf a buffer into which raw PCM content will be rendered.
 * \param len the number of bytes to render into `buf`.
 */
void pmd_renderer ( short *buf , int len );
/**
 * \brief Stops playback and frees internal structures.
 */
void pmd_stop ( void );
/**
 * \brief Writes the title of the currently-open song into `dest`.
 *        The normal encoding of PMD songs is Shift-JIS, but this can contain data in any arbitrary encoding.
 *
 * \param title the destination string.
 */
void pmd_get_title( char *dest );
/**
 * \brief Writes the composer of the currently-open song into `dest`.
 *        The normal encoding of PMD songs is Shift-JIS, but this can contain data in any arbitrary encoding.
 *
 * \param title the destination string.
 */
void pmd_get_compo( char *dest );

/**
 * \brief Returns the number of tracks in the song.
 *
 * \return the number of tracks in the song.
 */
int pmd_get_tracks( void );
/**
 * \brief Retrieves the notes being played in the current frame.
 *
 * Retrieves the notes being played in the current frame; this is frequently useful for visualization purposes.
 * Writes an array of `int` into the target pointer for up to the requested number of tracks.
 * Each integer represents the note being played within 12-note octaves.
 *
 * \param notes a pointer into which note data will be written.
 * \param len the number of tracks' worth of notes to read; usually the output of pmd_get_tracks().
 */
void pmd_get_current_notes ( int *notes , int len );


#endif

#ifdef __cplusplus
}
#endif
