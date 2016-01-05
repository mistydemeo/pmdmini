pmdmini
=======

pmdmini is a C library with a simple API which can play back MDX chiptunes from the [PC-98](https://en.wikipedia.org/wiki/NEC_PC-9801). The PC-98 was a very popular series of Japanese home computers. With its [Yamaha YM2203](https://en.wikipedia.org/wiki/Yamaha_YM2203) or [YM2608](https://en.wikipedia.org/wiki/Yamaha_YM2608) sound chip, for which many games and songs were written; the Professional Music Driver (PMD) library was a popular music library created by M. Kajihara. pmdmini allows playing back music written using PMD.

Some sample PMD music can be found at the [Modland FTP](http://www.exotica.org.uk/mediawiki/index.php?title=Special%3AModland&md=search&mod=&aut=&for=pmd&col=&ins=) and at the website of [Zun](http://www16.big.or.jp/~zun/html/pmd.html) (creator of the Touhou series of games).

Usage
=====

Detailed API documentation is available in the pmdmini.h header file, but the following sample program shows how to use mdxmini to open a file, extract some metadata, and play back music:

```c
// Initializes the library, before performing any other actions.
pmd_init();
// Check if the file is a valid PMD file before doing anything else!
int is_valid = pmd_is_pmd(path_to_file);
if (!is_valid) {
    fprintf(stderr, "Failed to open input file: %s\n", path_to_file);
    return 1;
}

// Before playback begins, call pmd_setrate to set the preferred sampling rate for generated audio.
int playback_rate = 48000;
pmd_setrate(playback_rate);

// Opens the file on disk and prepares the player for playback.
pmd_play(path_to_file, path_to_samples);

// Get the song duration, in whole seconds.
int length = pmd_length_sec();
printf("Song length: %i seconds\n", length);

// pmd_get_title allows the song's title to be fetched; this is usually encoded in Shift-JIS.
char title[1024];
pmd_get_title(title);
printf("Title: %s\n", title);
// The composer is stored separately; this is also Shift-JIS.
char compo[1024];
pmd_get_compo(compo);
printf("Composer: %s\n", title);

// For playback, define a buffer into which we'll render raw PCM data.
int buf_len = 8192;
short buf[buf_len];
// Number of channels, which we'll fetch for display later.
// This is constant for a given song, so just fetch it once.
int number_of_channels = pmd_get_tracks();
printf("Number of channels: %i\n", number_of_channels);
// A buffer into which we'll write information about the notes being played in a given frame.
int notes[32];

int position;

// Track the number of buffers played so far, which is useful to calculate the current position.
int played_buffers = 0;
int finished = 1;

// The playback loop!
while (finished == 1)
{
    // Calculate the song position based on the buffer size and frequency.
    position = played_buffers / (((playback_rate * 16 * 2) / 8) / (buf_len * 2));
    printf("Current position: %i / %i\n", position, length);

    // Render samples into the buffer
    pmd_renderer(buf, buf_len / 2);
    // Check the position against the reported duration to determine if playback is finished
    if (position >= length) {
        finished = 0;
    }

    // Do something with the calculated sample here; this is platform-dependent, so this intro will omit it.

    // Fill the note buffer with information about the notes in the current frame
    pmd_get_current_notes(notes, number_of_channels);

    for (int i = 0; i < number_of_channels; i++) {
        printf("Note for channel %i is %i\n", i, notes[i]);
    }

    // Increment the count of played buffers.
    played_buffers++;
}

// When playback is over, finalize the library's state.
pmd_stop();
```

Programs using pmdmini
======================

* [MDXPLAYER for Android](https://github.com/mistydemeo/mdxplayer), by BouKiCHi
* [ruby-mdxplay](https://github.com/mistydemeo/ruby-mdxplay)
* [Paula](https://github.com/mistydemeo/paula)
* [Modizer](http://yoyofr.blogspot.ca/p/modizer.html) by [yoyofr](http://yoyofr.blogspot.ca)

Credits
=======

* KAJIHARA Mashahiro - original author of the PMD sound driver for PC-9801
* AGAWA Koji - Maintainer of [PMDXMMS](http://web.archive.org/web/20040215211934/http://www.self-core.org/~kaoru-k/wiki/PmdXmms.html), on which pmdmini was based
* [PMDWin / C60](http://c60.la.coocan.jp) - PMD sound engine for Windows, on which PMDXMMS was based
* M88 / cisc - author of OPNA FM sound generator used by PMDWin
* PPZ8 / Ukky - author of PPZ8 PCM driver
* [BouKiCHi](http://clogging.blog57.fc2.com) - author of the pmdmini library, and of the Android mdxplayer
* [Misty De Meo](http://www.mistys-internet.website) - bugfixes and improvements to mdxmini, current maintainer
