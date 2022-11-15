<?xml version="1.0" encoding="UTF-8"?>
<!--
    Integer Scale, by Themaister

    Regardless of the output size requested by the host application, this
    shader always renders at an output size that's an integer multiple of the
    original input image size.

    From this forum post:

	http://board.byuu.org/viewtopic.php?p=32518#p32518
 -->
<shader language="GLSL">
   <vertex><![CDATA[

      float minimum(vec2 x)
      {
         if (x.x > x.y)
            return x.y;
         else
            return x.x;
      }

      uniform vec2 rubyInputSize;
      uniform vec2 rubyTextureSize;
      uniform vec2 rubyOutputSize;

      void main()
      {
         gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

         float box_scale = minimum(floor(rubyOutputSize / rubyInputSize));

         vec2 scale = (rubyOutputSize / rubyInputSize) / box_scale;
         vec2 middle = 0.5 * rubyInputSize / rubyTextureSize;
         vec2 diff = gl_MultiTexCoord0.xy - middle;
         gl_TexCoord[0].xy = middle + diff * scale;
      }
  ]]></vertex>
  <fragment filter="nearest"><![CDATA[
     uniform sampler2D rubyTexture;
     void main() { gl_FragColor = texture2D(rubyTexture, gl_TexCoord[0].xy); }
  ]]></fragment>
</shader>
