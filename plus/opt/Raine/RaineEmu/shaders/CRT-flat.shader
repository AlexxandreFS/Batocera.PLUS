<?xml version="1.0" encoding="UTF-8"?>
<!--
    CRT-flat shader

    Copyright (C) 2010, 2011 cgwg, Themaister, DOLLS

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the Free
    Software Foundation; either version 2 of the License, or (at your option)
    any later version.

    (cgwg gave their consent to have the original version of this shader
    distributed under the GPL in this message:

        http://board.byuu.org/viewtopic.php?p=26075#p26075

        "Feel free to distribute my shaders under the GPL. After all, the
        barrel distortion code was taken from the Curvature shader, which is
        under the GPL."
    )
    -->
<shader language="GLSL">
    <vertex><![CDATA[
        uniform vec2 rubyInputSize;
        uniform vec2 rubyOutputSize;
        uniform vec2 rubyTextureSize;

        // Define some calculations that will be used in fragment shader.
        varying vec2 one;
        varying float mod_factor;
        varying vec2 ratio_scale;

        void main()
        {
                // Do the standard vertex processing
                gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

                // Precalculate a bunch of useful values we'll need in the fragment
                // shader.

                // The size of one texel, in texture-coordinates
                one = 1.0 / rubyTextureSize;

                // Texel coordinates of the texel we're drawing.
                ratio_scale = gl_MultiTexCoord0.xy * rubyTextureSize - vec2(0.5);

                // Resulting X pixel-coordinate of the pixel we're drawing.
                mod_factor  = ratio_scale.x * rubyOutputSize.x / rubyInputSize.x;
        }
    ]]></vertex>
    <fragment><![CDATA[
        uniform sampler2D rubyTexture;
        uniform vec2 rubyInputSize;
        uniform vec2 rubyOutputSize;
        uniform vec2 rubyTextureSize;

        varying vec2 one;
        varying float mod_factor;
        varying vec2 ratio_scale;

        // Comment the next line to disable interpolation in linear gamma (and gain speed)
        #define LINEAR_PROCESSING

        // Compensate for 16-235 level range as per Rec. 601
        #define REF_LEVELS

        // Simulate a CRT gamma of 2.4
        #define inputGamma  2.4

        // Compensate for the standard sRGB gamma of 2.2
        #define outputGamma 2.2

        // Macros
        #define FIX(c) max(abs(c), 1e-5);
        #define PI 3.141592653589

        #ifdef REF_LEVELS
        #       define LEVELS(c) max((c - 16.0 / 255.0) * 255.0 / (235.0 - 16.0), 0.0)
        #else
        #       define LEVELS(c) c
        #endif

        #ifdef LINEAR_PROCESSING
        #       define TEX2D(c) pow(LEVELS(texture2D(rubyTexture, (c))), vec4(inputGamma))
        #else
        #       define TEX2D(c) LEVELS(texture2D(rubyTexture, (c)))
        #endif

        // Calculate the influence of a scanline on the current pixel.
        //
        // 'distance' is the distance in texture coordinates from the current
        // pixel to the scanline in question.
        // 'color' is the colour of the scanline at the horizontal location of
        // the current pixel.
        vec4 scanlineWeights(float distance, vec4 color)
        {
                // The "width" of the scanline beam is set as 2*(1 + x^4) for
                // each RGB channel.
                vec4 wid = 2.0 + 2.0 * pow(color, vec4(4.0));

                // The "weights" lines basically specify the formula that gives
                // you the profile of the beam, i.e. the intensity as
                // a function of distance from the vertical center of the
                // scanline. In this case, it is gaussian if width=2, and
                // becomes nongaussian for larger widths. Ideally this should
                // be normalized so that the integral across the beam is
                // independent of its width. That is, for a narrower beam
                // "weights" should have a higher peak at the center of the
                // scanline than for a wider beam.
                vec4 weights = vec4(distance / 0.3);
                return 1.7 * exp(-pow(weights * inversesqrt(0.5 * wid), wid)) / (0.6 + 0.2 * wid);
        }

        void main()
        {
                // Here's a helpful diagram to keep in mind while trying to
                // understand the code:
                //
                //  |      |      |      |      |
                // -------------------------------
                //  |      |      |      |      |
                //  |  01  |  11  |  21  |  31  | <-- current scanline
                //  |      | @    |      |      |
                // -------------------------------
                //  |      |      |      |      |
                //  |  02  |  12  |  22  |  32  | <-- next scanline
                //  |      |      |      |      |
                // -------------------------------
                //  |      |      |      |      |
                //
                // Each character-cell represents a pixel on the output
                // surface, "@" represents the current pixel (always somewhere
                // in the bottom half of the current scan-line, or the top-half
                // of the next scanline). The grid of lines represents the
                // edges of the texels of the underlying texture.

                // Of all the pixels that are mapped onto the texel we are
                // currently rendering, which pixel are we currently rendering?
                vec2 uv_ratio = fract(ratio_scale);

                // Calculate Lanczos scaling coefficients describing the effect
                // of various neighbour texels in a scanline on the current
                // pixel.
                vec4 coeffs = PI * vec4(1.0 + uv_ratio.x, uv_ratio.x, 1.0 - uv_ratio.x, 2.0 - uv_ratio.x);

                // Prevent division by zero
                coeffs = FIX(coeffs);

                // Lanczos2 kernel
                coeffs = 2.0 * sin(coeffs) * sin(coeffs / 2.0) / (coeffs * coeffs);

                // Normalize
                coeffs /= dot(coeffs, vec4(1.0));

                // Snap to the center of the underlying texel.
                vec2 xy = (floor(ratio_scale) + vec2(0.5)) / rubyTextureSize;

                // Calculate the effective colour of the current and next
                // scanlines at the horizontal location of the current pixel,
                // using the Lanczos coefficients above.
                vec4 col  = clamp(mat4(
                        TEX2D(xy + vec2(-one.x, 0.0)),
                        TEX2D(xy),
                        TEX2D(xy + vec2(one.x, 0.0)),
                        TEX2D(xy + vec2(2.0 * one.x, 0.0))) * coeffs,
                        0.0, 1.0);
                vec4 col2 = clamp(mat4(
                        TEX2D(xy + vec2(-one.x, one.y)),
                        TEX2D(xy + vec2(0.0, one.y)),
                        TEX2D(xy + one),
                        TEX2D(xy + vec2(2.0 * one.x, one.y))) * coeffs,
                        0.0, 1.0);

        #ifndef LINEAR_PROCESSING
                col  = pow(col , vec4(inputGamma));
                col2 = pow(col2, vec4(inputGamma));
        #endif

                // Calculate the influence of the current and next scanlines on
                // the current pixel.
                vec4 weights  = scanlineWeights(uv_ratio.y, col);
                vec4 weights2 = scanlineWeights(1.0 - uv_ratio.y, col2);
                vec3 mul_res  = (col * weights + col2 * weights2).xyz;

                // dot-mask emulation:
                // Output pixels are alternately tinted green and magenta.
                vec3 dotMaskWeights = mix(
                        vec3(1.0, 0.7, 1.0),
                        vec3(0.7, 1.0, 0.7),
                        floor(mod(mod_factor, 2.0))
                    );

                mul_res *= dotMaskWeights;

                // Convert the image gamma for display on our output device.
                mul_res = pow(mul_res, vec3(1.0 / outputGamma));

                // Color the texel
                gl_FragColor = vec4(mul_res, 1.0);
        }
    ]]></fragment>
</shader>
