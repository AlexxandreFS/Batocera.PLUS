<?xml version="1.0" encoding="UTF-8"?>
<!--
    Copyright (C) 2010 Team XBMC
    http://www.xbmc.org
    Copyright (C) 2011 Stefanos A.
    http://www.opentk.com

This Program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This Program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with XBMC; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
http://www.gnu.org/copyleft/gpl.html
-->
<!--
    From this forum post:

	http://board.byuu.org/viewtopic.php?p=33488#p33488
-->
<shader language="GLSL">
    <vertex><![CDATA[
	void main()
	{
	    gl_TexCoord[0] = gl_MultiTexCoord0;         //center
	    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	}
    ]]></vertex>

    <fragment><![CDATA[
	uniform sampler2D rubyTexture;
	uniform vec2 rubyTextureSize;

	float weight(float x)
	{
	    float ax = abs(x);
	    const float B = 0.1;
	    const float C = 0.5;

	    if (ax < 1.0) {
		return (
		    pow(x, 2.0) * (
			(12.0 - 9.0 * B - 6.0 * C) * ax +
			(-18.0 + 12.0 * B + 6.0 * C)
		    ) +
		    (6.0 - 2.0 * B)
		) / 6.0;

	    } else if ((ax >= 1.0) && (ax < 2.0)) {
		return (
		    pow(x, 2.0) * (
			(-B - 6.0 * C) * ax +
			(6.0 * B + 30.0 * C)
		    ) +
		    (-12.0 * B - 48.0 * C) * ax +
		    (8.0 * B + 24.0 * C)
		) / 6.0;

	    } else {
		return 0.0;
	    }
	}

	vec4 weight4(float x)
	{
	    return vec4(
		weight(x + 1.0),
		weight(x),
		weight(1.0 - x),
		weight(2.0 - x));
	}

	vec3 pixel(float xpos, float ypos)
	{
	    return texture2D(rubyTexture, vec2(xpos, ypos)).rgb;
	}

	vec3 line(float ypos, vec4 xpos, vec4 linetaps)
	{
	    return
		pixel(xpos.r, ypos) * linetaps.r +
		pixel(xpos.g, ypos) * linetaps.g +
		pixel(xpos.b, ypos) * linetaps.b +
		pixel(xpos.a, ypos) * linetaps.a;
	}

	void main()
	{
	    vec2 stepxy = 1.0 / rubyTextureSize.xy;
	    vec2 pos = gl_TexCoord[0].xy + stepxy * 0.5;
	    vec2 f = fract(pos / stepxy);

	    vec4 linetaps   = weight4(f.x);
	    vec4 columntaps = weight4(f.y);

	    // make sure all taps added together is exactly 1.0, otherwise some
	    // (very small) distortion can occur
	    linetaps /= 
		linetaps.r +
		linetaps.g +
		linetaps.b +
		linetaps.a;
	    columntaps /=
		columntaps.r +
		columntaps.g +
		columntaps.b +
		columntaps.a;

	    vec2 xystart = (-1.5 - f) * stepxy + pos;
	    vec4 xpos = vec4(
		xystart.x,
		xystart.x + stepxy.x,
		xystart.x + stepxy.x * 2.0,
		xystart.x + stepxy.x * 3.0);

	    gl_FragColor.rgb =
		line(xystart.y                 , xpos, linetaps) * columntaps.r +
		line(xystart.y + stepxy.y      , xpos, linetaps) * columntaps.g +
		line(xystart.y + stepxy.y * 2.0, xpos, linetaps) * columntaps.b +
		line(xystart.y + stepxy.y * 3.0, xpos, linetaps) * columntaps.a;

	    gl_FragColor.a = 1.0;
	}
    ]]></fragment>
</shader>
