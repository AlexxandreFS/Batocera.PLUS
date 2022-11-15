<?xml version="1.0" encoding="UTF-8"?>
<!--
    Copyright (c) 2011, 2012 Fes, Themaister and hunterk

    Permission to use, copy, modify, and/or distribute this software for any
    purpose with or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
    SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
    IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

	This shader is a combination of Themaister's scanline shader with Fes' pixellate shader.

    (Fes gave their permission to have this shader distributed under this
    licence in this forum post:

        http://board.byuu.org/viewtopic.php?p=57295#p57295

    )

-->
<shader language="GLSL">
    <vertex><![CDATA[
	 uniform vec2 rubyTextureSize;
     uniform vec2 rubyInputSize;
     uniform vec2 rubyOutputSize;

     varying vec2 omega;
        void main()
        {
                gl_Position    = ftransform();
                gl_TexCoord[0] = gl_MultiTexCoord0;
				omega = vec2(3.1415 * rubyOutputSize.x * rubyTextureSize.x / rubyInputSize.x, 2.0 * 3.1415 * rubyTextureSize.y);
        }
    ]]></vertex>

    <fragment filter="nearest"><![CDATA[
        uniform sampler2D rubyTexture;
        uniform vec2      rubyTextureSize;
		uniform vec2 rubyInputSize;
		uniform vec2 rubyOutputSize;

        #define round(x) floor( (x) + 0.5 )

		varying vec2 omega;

     const float base_brightness = 0.95;
     const vec2 sine_comp = vec2(0.05, 0.15);

        void main()
        {
                vec2 texelSize = 1.0 / rubyTextureSize;
                vec2 texCoord = gl_TexCoord[0].xy;

					//scanline stuff
					vec4 c11 = texture2D(rubyTexture, gl_TexCoord[0].xy);
					vec4 scanline = c11 * (base_brightness + dot(sine_comp * sin(gl_TexCoord[0].xy * omega), vec2(1.0)));

                vec2 range = vec2(abs(dFdx(texCoord.x)), abs(dFdy(texCoord.y)));
                range = range / 2.0 * 0.999;

                float left   = texCoord.x - range.x;
                float top    = texCoord.y + range.y;
                float right  = texCoord.x + range.x;
                float bottom = texCoord.y - range.y;

                vec4 topLeftColor     = texture2D(rubyTexture, vec2(left, top));
                vec4 bottomRightColor = texture2D(rubyTexture, vec2(right, bottom));
                vec4 bottomLeftColor  = texture2D(rubyTexture, vec2(left, bottom));
                vec4 topRightColor    = texture2D(rubyTexture, vec2(right, top));

                vec2 border = clamp(
                        round(texCoord / texelSize) * texelSize,
                        vec2(left, bottom),
                        vec2(right, top)
                    );

                float totalArea = 4.0 * range.x * range.y;

                vec4 averageColor;
                averageColor  = ((border.x - left)  * (top - border.y)    / totalArea) * topLeftColor;
                averageColor += ((right - border.x) * (border.y - bottom) / totalArea) * bottomRightColor;
                averageColor += ((border.x - left)  * (border.y - bottom) / totalArea) * bottomLeftColor;
                averageColor += ((right - border.x) * (top - border.y)    / totalArea) * topRightColor;

                gl_FragColor = clamp((averageColor * scanline), 0.0, 1.0);
        }
    ]]></fragment>
</shader>
