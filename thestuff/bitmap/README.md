# bitmap

Cobbled together c++ 'library' for creating bitmap files.

I wrote this mainly for tinyrenderer.

I won't give proper documentation because no one should ever use this, but you basically init a bitmap with a width, height and color depth, then you can set individual pixels at specific coordinates. I don't think you'll be able to actually change the color depth to anything other than 24, but adding support for it should only require a few small modifications.

If you compile and run the main file, it should run 5 tests for you.

Here's what those should look like:

## Two Colors
Only 8x4 pixels, half of them black, the other half white.
![Two Colors](https://i.imgur.com/41fLivP.png)
## Chess Board
8x8 pixels in a chess board pattern.
![Chess Board](https://i.imgur.com/2APljpN.png)
## Spectrum
Not really the color spectrum but still looks kinda cool.
![Spectrum](https://i.imgur.com/2G3R3dS.png)
## Gradient
Linear interpolation between two colors.
![Gradient](https://i.imgur.com/IE11spO.png)
## Pride Flag
I had a huge mistake in the way padding bits were being written, but it didn't affect any other test. So everything was fine, except for this image. Took me way too long to debug this. And I think at some point during that time it got flipped.
![Pride Flag](https://i.imgur.com/Am61azp.png)
