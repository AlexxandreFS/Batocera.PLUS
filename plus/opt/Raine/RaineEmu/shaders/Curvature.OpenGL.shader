<?xml version="1.0" encoding="UTF-8"?>
<shader language="GLSL">
  <fragment filter="linear"><![CDATA[
    uniform sampler2D rubyTexture;
    uniform vec2 rubyInputSize;
    uniform vec2 rubyTextureSize;

    #define distortion 0.2

    vec2 barrelDistortion(vec2 coord) {
      vec2 cc = coord - 0.5;
      float dist = dot(cc, cc);
      return coord + cc * (dist + distortion * dist * dist) * distortion;
    }

    void main(void) {
      vec2 coord = barrelDistortion (gl_TexCoord[0] * rubyTextureSize / rubyInputSize) * rubyInputSize / rubyTextureSize;

      gl_FragColor = texture2D(rubyTexture, coord);
    }
  ]]></fragment>
</shader>
