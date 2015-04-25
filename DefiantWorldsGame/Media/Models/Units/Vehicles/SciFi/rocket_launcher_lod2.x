xof 0303txt 0032

// DirectX 9.0 file
// Creator: Ultimate Unwrap3D Pro v3.19
// Website: http://www.unwrap3d.com
// Time: Sun Nov 22 10:14:09 2009

// Start of Templates

template VertexDuplicationIndices {
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}

template FVFData {
 <b6e70a0e-8ef9-4e83-94ad-ecc8b0c04897>
 DWORD dwFVF;
 DWORD nDWords;
 array DWORD data[nDWords];
}

template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template FrameTransformMatrix {
 <F6F23F41-7686-11cf-8F52-0040333594A3>
 Matrix4x4 frameMatrix;
}

template Frame {
 <3D82AB46-62DA-11cf-AB39-0020AF71E433>
 [...]
}

template FloatKeys {
 <10DD46A9-775B-11cf-8F52-0040333594A3>
 DWORD nValues;
 array FLOAT values[nValues];
}

template TimedFloatKeys {
 <F406B180-7B3B-11cf-8F52-0040333594A3>
 DWORD time;
 FloatKeys tfkeys;
}

template AnimationKey {
 <10DD46A8-775B-11cf-8F52-0040333594A3>
 DWORD keyType;
 DWORD nKeys;
 array TimedFloatKeys keys[nKeys];
}

template AnimationOptions {
 <E2BF56C0-840F-11cf-8F52-0040333594A3>
 DWORD openclosed;
 DWORD positionquality;
}

template Animation {
 <3D82AB4F-62DA-11cf-AB39-0020AF71E433>
 [...]
}

template AnimationSet {
 <3D82AB50-62DA-11cf-AB39-0020AF71E433>
 [Animation]
}

template XSkinMeshHeader {
 <3CF169CE-FF7C-44ab-93C0-F78F62D172E2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}

template SkinWeights {
 <6F0D123B-BAD2-4167-A0D0-80224F25FABB>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array FLOAT weights[nWeights];
 Matrix4x4 matrixOffset;
}

template AnimTicksPerSecond {
 <9E415A43-7BA6-4a73-8743-B73D47E88476>
 DWORD AnimTicksPerSecond;
}

AnimTicksPerSecond {
 4800;
}

// Start of Frames

Frame Launcher_Rocket_lod2 {
   FrameTransformMatrix {
    1.000000, 0.000000, 0.000000, 0.000000,
    0.000000, 1.000000, 0.000000, 0.000000,
    0.000000, 0.000000, 1.000000, 0.000000,
    0.000000, 0.000000, 0.000000, 1.000000;;
   }

   Mesh Launcher_Rocket_lod2 {
    114;
    -0.007714; 0.792131; -0.690881;,
    -0.484505; 0.790348; 0.590232;,
    -0.484505; 0.790347; -0.690888;,
    -0.007714; 0.792131; 0.590239;,
    -0.484504; 1.177128; 0.590224;,
    -0.007714; 1.178911; -0.690886;,
    -0.484504; 1.177128; -0.690893;,
    -0.007714; 1.178911; 0.590238;,
    -0.484504; 1.177128; -0.690893;,
    -0.007714; 1.178911; -0.690886;,
    -0.007714; 0.792131; -0.690881;,
    -0.524577; 1.046132; -0.690882;,
    -0.484505; 0.790347; -0.690888;,
    -0.083996; 0.854080; 0.590234;,
    -0.429037; 0.854079; 0.590246;,
    -0.484505; 0.790348; 0.590232;,
    -0.007714; 0.792131; 0.590239;,
    -0.429036; 1.113396; 0.590237;,
    -0.484504; 1.177128; 0.590224;,
    -0.007714; 1.178911; 0.590238;,
    -0.083996; 1.113396; 0.590234;,
    -0.368379; 0.595944; -0.345775;,
    -0.368379; 0.595944; 0.415068;,
    0.372700; 0.595944; -0.345773;,
    0.372699; 0.595944; 0.415068;,
    0.255692; 0.507712; 0.458441;,
    -0.401915; -0.002010; 0.729536;,
    0.474356; -0.002010; 0.729533;,
    -0.251369; 0.507712; 0.458439;,
    0.633273; -0.002010; 0.726635;,
    0.633273; -0.002010; -0.553030;,
    -0.633273; -0.002010; -0.553029;,
    -0.633273; -0.002010; 0.726634;,
    0.372699; 0.595944; 0.415068;,
    0.474356; -0.002010; 0.729533;,
    0.633273; -0.002010; 0.726635;,
    0.255692; 0.507712; 0.458441;,
    -0.368379; 0.595944; 0.415068;,
    -0.251369; 0.507712; 0.458439;,
    -0.633273; -0.002010; 0.726634;,
    -0.401915; -0.002010; 0.729536;,
    -0.633273; -0.002010; -0.553029;,
    -0.368379; 0.595944; -0.345775;,
    -0.494813; -0.002010; -0.548172;,
    -0.288532; 0.532587; -0.361444;,
    0.372700; 0.595944; -0.345773;,
    0.297739; 0.532587; -0.358483;,
    0.633273; -0.002010; -0.553030;,
    0.492424; -0.002010; -0.548171;,
    0.469076; 0.793915; -0.690888;,
    0.469076; 0.793915; 0.590237;,
    -0.007714; 0.792131; -0.690881;,
    -0.007714; 0.792131; 0.590239;,
    0.469076; 1.180696; 0.590237;,
    0.469076; 1.180696; -0.690894;,
    -0.007714; 1.178911; -0.690886;,
    -0.007714; 1.178911; 0.590238;,
    -0.007714; 1.178911; -0.690886;,
    0.469076; 0.793915; -0.690888;,
    -0.007714; 0.792131; -0.690881;,
    0.469076; 1.180696; -0.690894;,
    0.509150; 1.049699; -0.690885;,
    0.413608; 0.857647; 0.590245;,
    0.068569; 0.857647; 0.590241;,
    0.469076; 0.793915; 0.590237;,
    -0.007714; 0.792131; 0.590239;,
    0.469076; 1.180696; 0.590237;,
    0.413608; 1.116964; 0.590240;,
    0.068568; 1.116964; 0.590241;,
    -0.007714; 1.178911; 0.590238;,
    0.491420; 1.282010; -0.715809;,
    0.491420; 1.273469; 0.663164;,
    0.491420; 0.757840; 0.653451;,
    0.491420; 0.766381; -0.725521;,
    0.442529; 1.273469; 0.663140;,
    0.442529; 1.282010; -0.715820;,
    0.442529; 0.757840; 0.653420;,
    0.442529; 0.766381; -0.725521;,
    -0.519200; 1.273882; -0.719805;,
    -0.519201; 0.758253; -0.729514;,
    -0.519201; 0.749712; 0.649434;,
    -0.519200; 1.265341; 0.659152;,
    -0.479700; 1.273882; -0.719824;,
    -0.479700; 1.265341; 0.659144;,
    -0.479701; 0.749712; 0.649426;,
    -0.479701; 0.758254; -0.729536;,
    -0.207556; 0.993368; 0.158715;,
    -0.235642; 0.600736; 0.281688;,
    0.237265; 0.600736; 0.281683;,
    0.209179; 0.993368; 0.158715;,
    0.209179; 0.993368; 0.158715;,
    0.237265; 0.600736; 0.281683;,
    0.237265; 0.600736; -0.144934;,
    0.209179; 0.993368; -0.098831;,
    -0.207556; 0.993368; -0.098836;,
    0.209179; 0.993368; -0.098831;,
    0.237265; 0.600736; -0.144934;,
    -0.235642; 0.600736; -0.144929;,
    -0.207556; 0.993368; 0.158715;,
    -0.207556; 0.993368; -0.098836;,
    -0.235642; 0.600736; -0.144929;,
    -0.235642; 0.600736; 0.281688;,
    -0.494813; -0.002010; -0.548172;,
    -0.288532; 0.532587; -0.361444;,
    0.492424; -0.002010; -0.548171;,
    0.297739; 0.532587; -0.358483;,
    0.413608; 1.116964; 0.590240;,
    0.068568; 1.116964; 0.590241;,
    0.413608; 0.857647; 0.590245;,
    0.068569; 0.857647; 0.590241;,
    -0.083996; 1.113396; 0.590234;,
    -0.429036; 1.113396; 0.590237;,
    -0.083996; 0.854080; 0.590234;,
    -0.429037; 0.854079; 0.590246;;
    72;
    3;0, 1, 2;,
    3;0, 3, 1;,
    3;4, 5, 6;,
    3;7, 5, 4;,
    3;8, 9, 10;,
    3;11, 8, 10;,
    3;11, 10, 12;,
    3;13, 14, 15;,
    3;16, 13, 15;,
    3;17, 18, 15;,
    3;14, 17, 15;,
    3;19, 18, 20;,
    3;20, 18, 17;,
    3;20, 13, 16;,
    3;19, 20, 16;,
    3;21, 22, 23;,
    3;22, 24, 23;,
    3;25, 26, 27;,
    3;25, 28, 26;,
    3;24, 29, 30;,
    3;23, 24, 30;,
    3;22, 21, 31;,
    3;32, 22, 31;,
    3;33, 34, 35;,
    3;33, 36, 34;,
    3;33, 37, 38;,
    3;33, 38, 36;,
    3;37, 39, 40;,
    3;38, 37, 40;,
    3;41, 42, 43;,
    3;42, 44, 43;,
    3;42, 45, 44;,
    3;44, 45, 46;,
    3;45, 47, 48;,
    3;46, 45, 48;,
    3;49, 50, 51;,
    3;50, 52, 51;,
    3;53, 54, 55;,
    3;56, 53, 55;,
    3;57, 58, 59;,
    3;57, 60, 61;,
    3;57, 61, 58;,
    3;62, 63, 64;,
    3;64, 63, 65;,
    3;66, 67, 62;,
    3;66, 62, 64;,
    3;67, 66, 68;,
    3;66, 69, 68;,
    3;68, 69, 63;,
    3;63, 69, 65;,
    3;70, 71, 72;,
    3;73, 70, 72;,
    3;74, 75, 76;,
    3;75, 77, 76;,
    3;78, 79, 80;,
    3;81, 78, 80;,
    3;82, 83, 84;,
    3;85, 82, 84;,
    3;86, 87, 88;,
    3;89, 86, 88;,
    3;90, 91, 92;,
    3;93, 90, 92;,
    3;94, 95, 96;,
    3;97, 94, 96;,
    3;98, 99, 100;,
    3;101, 98, 100;,
    3;102, 103, 104;,
    3;103, 105, 104;,
    3;106, 107, 108;,
    3;108, 107, 109;,
    3;110, 111, 112;,
    3;112, 111, 113;;

   MeshNormals {
    114;
    0.002642; -0.707108; -0.707100;,
    0.001567; -0.447233; 0.894416;,
    0.002656; -0.707093; -0.707116;,
    0.001358; -0.371384; 0.928478;,
    -0.002140; 0.554735; 0.832024;,
    -0.002648; 0.707094; -0.707115;,
    -0.001681; 0.447179; -0.894443;,
    -0.001419; 0.371389; 0.928476;,
    -0.001681; 0.447179; -0.894443;,
    -0.002648; 0.707094; -0.707115;,
    0.002642; -0.707108; -0.707100;,
    -0.000009; -0.000024; -1.000000;,
    0.002656; -0.707093; -0.707116;,
    0.000001; -0.000029; 1.000000;,
    -0.000070; -0.000059; 1.000000;,
    0.001567; -0.447233; 0.894416;,
    0.001358; -0.371384; 0.928478;,
    -0.000088; 0.000062; 1.000000;,
    -0.002140; 0.554735; 0.832024;,
    -0.001419; 0.371389; 0.928476;,
    -0.000027; 0.000037; 1.000000;,
    -0.219348; 0.605087; -0.765347;,
    -0.344097; 0.791578; 0.504977;,
    0.151949; 0.659368; -0.736305;,
    0.339111; 0.669504; 0.660884;,
    -0.005084; 0.460795; 0.887492;,
    0.002725; 0.467395; 0.884044;,
    -0.001404; 0.466642; 0.884445;,
    0.005499; 0.454135; 0.890916;,
    0.601765; 0.559307; 0.570135;,
    0.776166; 0.479964; -0.408903;,
    -0.773500; 0.484348; -0.408785;,
    -0.597625; 0.562468; 0.571379;,
    0.339111; 0.669504; 0.660884;,
    -0.001404; 0.466642; 0.884445;,
    0.601765; 0.559307; 0.570135;,
    -0.005084; 0.460795; 0.887492;,
    -0.344097; 0.791578; 0.504977;,
    0.005499; 0.454135; 0.890916;,
    -0.597625; 0.562468; 0.571379;,
    0.002725; 0.467395; 0.884044;,
    -0.773500; 0.484348; -0.408785;,
    -0.219348; 0.605087; -0.765347;,
    0.030708; 0.317688; -0.947698;,
    0.013732; 0.281695; -0.959406;,
    0.151949; 0.659368; -0.736305;,
    -0.028366; 0.277252; -0.960378;,
    0.776166; 0.479964; -0.408903;,
    -0.030656; 0.320877; -0.946625;,
    0.001668; -0.447210; -0.894427;,
    0.002110; -0.554728; 0.832029;,
    0.002642; -0.707108; -0.707100;,
    0.001358; -0.371384; 0.928478;,
    -0.001638; 0.447228; 0.894418;,
    -0.002659; 0.707074; -0.707135;,
    -0.002648; 0.707094; -0.707115;,
    -0.001419; 0.371389; 0.928476;,
    -0.002648; 0.707094; -0.707115;,
    0.001668; -0.447210; -0.894427;,
    0.002642; -0.707108; -0.707100;,
    -0.002659; 0.707074; -0.707135;,
    -0.000006; -0.000033; -1.000000;,
    0.000028; -0.000018; 1.000000;,
    -0.000017; -0.000033; 1.000000;,
    0.002110; -0.554728; 0.832029;,
    0.001358; -0.371384; 0.928478;,
    -0.001638; 0.447228; 0.894418;,
    0.000010; 0.000025; 1.000000;,
    -0.000007; 0.000020; 1.000000;,
    -0.001419; 0.371389; 0.928476;,
    1.000000; 0.000000; 0.000000;,
    1.000000; 0.000000; 0.000000;,
    1.000000; 0.000000; 0.000000;,
    1.000000; -0.000000; -0.000000;,
    -1.000000; 0.000000; -0.000000;,
    -1.000000; 0.000000; -0.000000;,
    -1.000000; 0.000000; -0.000000;,
    -1.000000; 0.000000; -0.000000;,
    -1.000000; 0.000001; -0.000000;,
    -1.000000; 0.000001; -0.000000;,
    -1.000000; 0.000001; -0.000000;,
    -1.000000; 0.000002; 0.000000;,
    1.000000; -0.000002; -0.000000;,
    1.000000; -0.000002; -0.000000;,
    1.000000; -0.000002; -0.000000;,
    1.000000; -0.000002; -0.000000;,
    -0.697901; 0.259044; 0.667705;,
    -0.697899; 0.259048; 0.667706;,
    0.442320; 0.296713; 0.846354;,
    0.884634; 0.195814; 0.423178;,
    0.884634; 0.195814; 0.423178;,
    0.442320; 0.296713; 0.846354;,
    0.702389; 0.132355; -0.699380;,
    0.702393; 0.132363; -0.699374;,
    -0.444596; 0.135754; -0.885384;,
    0.702393; 0.132363; -0.699374;,
    0.702389; 0.132355; -0.699380;,
    -0.889194; 0.115576; -0.442692;,
    -0.697901; 0.259044; 0.667705;,
    -0.444596; 0.135754; -0.885384;,
    -0.889194; 0.115576; -0.442692;,
    -0.697899; 0.259048; 0.667706;,
    0.030708; 0.317688; -0.947698;,
    0.013732; 0.281695; -0.959406;,
    -0.030656; 0.320877; -0.946625;,
    -0.028366; 0.277252; -0.960378;,
    0.000010; 0.000025; 1.000000;,
    -0.000007; 0.000020; 1.000000;,
    0.000028; -0.000018; 1.000000;,
    -0.000017; -0.000033; 1.000000;,
    -0.000027; 0.000037; 1.000000;,
    -0.000088; 0.000062; 1.000000;,
    0.000001; -0.000029; 1.000000;,
    -0.000070; -0.000059; 1.000000;;
    72;
    3;0, 1, 2;,
    3;0, 3, 1;,
    3;4, 5, 6;,
    3;7, 5, 4;,
    3;8, 9, 10;,
    3;11, 8, 10;,
    3;11, 10, 12;,
    3;13, 14, 15;,
    3;16, 13, 15;,
    3;17, 18, 15;,
    3;14, 17, 15;,
    3;19, 18, 20;,
    3;20, 18, 17;,
    3;20, 13, 16;,
    3;19, 20, 16;,
    3;21, 22, 23;,
    3;22, 24, 23;,
    3;25, 26, 27;,
    3;25, 28, 26;,
    3;24, 29, 30;,
    3;23, 24, 30;,
    3;22, 21, 31;,
    3;32, 22, 31;,
    3;33, 34, 35;,
    3;33, 36, 34;,
    3;33, 37, 38;,
    3;33, 38, 36;,
    3;37, 39, 40;,
    3;38, 37, 40;,
    3;41, 42, 43;,
    3;42, 44, 43;,
    3;42, 45, 44;,
    3;44, 45, 46;,
    3;45, 47, 48;,
    3;46, 45, 48;,
    3;49, 50, 51;,
    3;50, 52, 51;,
    3;53, 54, 55;,
    3;56, 53, 55;,
    3;57, 58, 59;,
    3;57, 60, 61;,
    3;57, 61, 58;,
    3;62, 63, 64;,
    3;64, 63, 65;,
    3;66, 67, 62;,
    3;66, 62, 64;,
    3;67, 66, 68;,
    3;66, 69, 68;,
    3;68, 69, 63;,
    3;63, 69, 65;,
    3;70, 71, 72;,
    3;73, 70, 72;,
    3;74, 75, 76;,
    3;75, 77, 76;,
    3;78, 79, 80;,
    3;81, 78, 80;,
    3;82, 83, 84;,
    3;85, 82, 84;,
    3;86, 87, 88;,
    3;89, 86, 88;,
    3;90, 91, 92;,
    3;93, 90, 92;,
    3;94, 95, 96;,
    3;97, 94, 96;,
    3;98, 99, 100;,
    3;101, 98, 100;,
    3;102, 103, 104;,
    3;103, 105, 104;,
    3;106, 107, 108;,
    3;108, 107, 109;,
    3;110, 111, 112;,
    3;112, 111, 113;;
   }

   MeshTextureCoords {
    114;
    0.308671; 0.209266;,
    0.001561; 0.320547;,
    0.308455; 0.320547;,
    0.001560; 0.208257;,
    0.001119; 0.001934;,
    0.308560; 0.113470;,
    0.308013; 0.001934;,
    0.001339; 0.114462;,
    0.313578; 0.867765;,
    0.170240; 0.867765;,
    0.170240; 0.987186;,
    0.325951; 0.908211;,
    0.313578; 0.987186;,
    0.708602; 0.853913;,
    0.809134; 0.853913;,
    0.825296; 0.872482;,
    0.690033; 0.872482;,
    0.809134; 0.778357;,
    0.825296; 0.759788;,
    0.690033; 0.759788;,
    0.708602; 0.778357;,
    0.522066; 0.002730;,
    0.521408; 0.252388;,
    0.629727; 0.002509;,
    0.625878; 0.252390;,
    0.545402; 0.583238;,
    0.777082; 0.745067;,
    0.464449; 0.743282;,
    0.721683; 0.584265;,
    0.831614; 0.348673;,
    0.813367; 0.048418;,
    0.310909; 0.001297;,
    0.310913; 0.354182;,
    0.443374; 0.309507;,
    0.407668; 0.515250;,
    0.348080; 0.514512;,
    0.487570; 0.338330;,
    0.721120; 0.306349;,
    0.677603; 0.336166;,
    0.830987; 0.509105;,
    0.744289; 0.511509;,
    0.842888; 0.739165;,
    0.756973; 0.540935;,
    0.796231; 0.739278;,
    0.728663; 0.557871;,
    0.497101; 0.542689;,
    0.522840; 0.559260;,
    0.398752; 0.742162;,
    0.445374; 0.741645;,
    0.310549; 0.655395;,
    0.003655; 0.655395;,
    0.311014; 0.543223;,
    0.004233; 0.542820;,
    0.005516; 0.334859;,
    0.312410; 0.334859;,
    0.312223; 0.448632;,
    0.005163; 0.447435;,
    0.162429; 0.867653;,
    0.019091; 0.987075;,
    0.162429; 0.987075;,
    0.019091; 0.867653;,
    0.006718; 0.908100;,
    0.708193; 0.974707;,
    0.810530; 0.974707;,
    0.691741; 0.993610;,
    0.829432; 0.993610;,
    0.691741; 0.878893;,
    0.708193; 0.897795;,
    0.810530; 0.897795;,
    0.829432; 0.878893;,
    0.385701; 0.677928;,
    0.003715; 0.677289;,
    0.003715; 0.824736;,
    0.385701; 0.824737;,
    0.044838; 0.845123;,
    0.348801; 0.845123;,
    0.044842; 0.660542;,
    0.347758; 0.660542;,
    0.385701; 0.679547;,
    0.385701; 0.826356;,
    0.003715; 0.826355;,
    0.003715; 0.678908;,
    0.348082; 0.845123;,
    0.046590; 0.845123;,
    0.046593; 0.660542;,
    0.347049; 0.660542;,
    0.844407; 0.005542;,
    0.837619; 0.146063;,
    0.999252; 0.145963;,
    0.993906; 0.005453;,
    0.876764; 0.435146;,
    0.829216; 0.590554;,
    0.998861; 0.589084;,
    0.979179; 0.434258;,
    0.984988; 0.149767;,
    0.849183; 0.149814;,
    0.840039; 0.287470;,
    0.994149; 0.287415;,
    0.993302; 0.291620;,
    0.843275; 0.292696;,
    0.833597; 0.431457;,
    0.999005; 0.431467;,
    0.712548; 0.524581;,
    0.656619; 0.352197;,
    0.451387; 0.524567;,
    0.506179; 0.352196;,
    0.416739; 0.593499;,
    0.332872; 0.593499;,
    0.416739; 0.656529;,
    0.332872; 0.656529;,
    0.405702; 0.519345;,
    0.323843; 0.519345;,
    0.405702; 0.580867;,
    0.323843; 0.580867;;
   }

   MeshVertexColors {
    114;
    0; 1.000000; 1.000000; 1.000000; 1.000000;,
    1; 1.000000; 1.000000; 1.000000; 1.000000;,
    2; 1.000000; 1.000000; 1.000000; 1.000000;,
    3; 1.000000; 1.000000; 1.000000; 1.000000;,
    4; 1.000000; 1.000000; 1.000000; 1.000000;,
    5; 1.000000; 1.000000; 1.000000; 1.000000;,
    6; 1.000000; 1.000000; 1.000000; 1.000000;,
    7; 1.000000; 1.000000; 1.000000; 1.000000;,
    8; 1.000000; 1.000000; 1.000000; 1.000000;,
    9; 1.000000; 1.000000; 1.000000; 1.000000;,
    10; 1.000000; 1.000000; 1.000000; 1.000000;,
    11; 1.000000; 1.000000; 1.000000; 1.000000;,
    12; 1.000000; 1.000000; 1.000000; 1.000000;,
    13; 1.000000; 1.000000; 1.000000; 1.000000;,
    14; 1.000000; 1.000000; 1.000000; 1.000000;,
    15; 1.000000; 1.000000; 1.000000; 1.000000;,
    16; 1.000000; 1.000000; 1.000000; 1.000000;,
    17; 1.000000; 1.000000; 1.000000; 1.000000;,
    18; 1.000000; 1.000000; 1.000000; 1.000000;,
    19; 1.000000; 1.000000; 1.000000; 1.000000;,
    20; 1.000000; 1.000000; 1.000000; 1.000000;,
    21; 1.000000; 1.000000; 1.000000; 1.000000;,
    22; 1.000000; 1.000000; 1.000000; 1.000000;,
    23; 1.000000; 1.000000; 1.000000; 1.000000;,
    24; 1.000000; 1.000000; 1.000000; 1.000000;,
    25; 1.000000; 1.000000; 1.000000; 1.000000;,
    26; 1.000000; 1.000000; 1.000000; 1.000000;,
    27; 1.000000; 1.000000; 1.000000; 1.000000;,
    28; 1.000000; 1.000000; 1.000000; 1.000000;,
    29; 1.000000; 1.000000; 1.000000; 1.000000;,
    30; 1.000000; 1.000000; 1.000000; 1.000000;,
    31; 1.000000; 1.000000; 1.000000; 1.000000;,
    32; 1.000000; 1.000000; 1.000000; 1.000000;,
    33; 1.000000; 1.000000; 1.000000; 1.000000;,
    34; 1.000000; 1.000000; 1.000000; 1.000000;,
    35; 1.000000; 1.000000; 1.000000; 1.000000;,
    36; 1.000000; 1.000000; 1.000000; 1.000000;,
    37; 1.000000; 1.000000; 1.000000; 1.000000;,
    38; 1.000000; 1.000000; 1.000000; 1.000000;,
    39; 1.000000; 1.000000; 1.000000; 1.000000;,
    40; 1.000000; 1.000000; 1.000000; 1.000000;,
    41; 1.000000; 1.000000; 1.000000; 1.000000;,
    42; 1.000000; 1.000000; 1.000000; 1.000000;,
    43; 1.000000; 1.000000; 1.000000; 1.000000;,
    44; 1.000000; 1.000000; 1.000000; 1.000000;,
    45; 1.000000; 1.000000; 1.000000; 1.000000;,
    46; 1.000000; 1.000000; 1.000000; 1.000000;,
    47; 1.000000; 1.000000; 1.000000; 1.000000;,
    48; 1.000000; 1.000000; 1.000000; 1.000000;,
    49; 1.000000; 1.000000; 1.000000; 1.000000;,
    50; 1.000000; 1.000000; 1.000000; 1.000000;,
    51; 1.000000; 1.000000; 1.000000; 1.000000;,
    52; 1.000000; 1.000000; 1.000000; 1.000000;,
    53; 1.000000; 1.000000; 1.000000; 1.000000;,
    54; 1.000000; 1.000000; 1.000000; 1.000000;,
    55; 1.000000; 1.000000; 1.000000; 1.000000;,
    56; 1.000000; 1.000000; 1.000000; 1.000000;,
    57; 1.000000; 1.000000; 1.000000; 1.000000;,
    58; 1.000000; 1.000000; 1.000000; 1.000000;,
    59; 1.000000; 1.000000; 1.000000; 1.000000;,
    60; 1.000000; 1.000000; 1.000000; 1.000000;,
    61; 1.000000; 1.000000; 1.000000; 1.000000;,
    62; 1.000000; 1.000000; 1.000000; 1.000000;,
    63; 1.000000; 1.000000; 1.000000; 1.000000;,
    64; 1.000000; 1.000000; 1.000000; 1.000000;,
    65; 1.000000; 1.000000; 1.000000; 1.000000;,
    66; 1.000000; 1.000000; 1.000000; 1.000000;,
    67; 1.000000; 1.000000; 1.000000; 1.000000;,
    68; 1.000000; 1.000000; 1.000000; 1.000000;,
    69; 1.000000; 1.000000; 1.000000; 1.000000;,
    70; 1.000000; 1.000000; 1.000000; 1.000000;,
    71; 1.000000; 1.000000; 1.000000; 1.000000;,
    72; 1.000000; 1.000000; 1.000000; 1.000000;,
    73; 1.000000; 1.000000; 1.000000; 1.000000;,
    74; 1.000000; 1.000000; 1.000000; 1.000000;,
    75; 1.000000; 1.000000; 1.000000; 1.000000;,
    76; 1.000000; 1.000000; 1.000000; 1.000000;,
    77; 1.000000; 1.000000; 1.000000; 1.000000;,
    78; 1.000000; 1.000000; 1.000000; 1.000000;,
    79; 1.000000; 1.000000; 1.000000; 1.000000;,
    80; 1.000000; 1.000000; 1.000000; 1.000000;,
    81; 1.000000; 1.000000; 1.000000; 1.000000;,
    82; 1.000000; 1.000000; 1.000000; 1.000000;,
    83; 1.000000; 1.000000; 1.000000; 1.000000;,
    84; 1.000000; 1.000000; 1.000000; 1.000000;,
    85; 1.000000; 1.000000; 1.000000; 1.000000;,
    86; 1.000000; 1.000000; 1.000000; 1.000000;,
    87; 1.000000; 1.000000; 1.000000; 1.000000;,
    88; 1.000000; 1.000000; 1.000000; 1.000000;,
    89; 1.000000; 1.000000; 1.000000; 1.000000;,
    90; 1.000000; 1.000000; 1.000000; 1.000000;,
    91; 1.000000; 1.000000; 1.000000; 1.000000;,
    92; 1.000000; 1.000000; 1.000000; 1.000000;,
    93; 1.000000; 1.000000; 1.000000; 1.000000;,
    94; 1.000000; 1.000000; 1.000000; 1.000000;,
    95; 1.000000; 1.000000; 1.000000; 1.000000;,
    96; 1.000000; 1.000000; 1.000000; 1.000000;,
    97; 1.000000; 1.000000; 1.000000; 1.000000;,
    98; 1.000000; 1.000000; 1.000000; 1.000000;,
    99; 1.000000; 1.000000; 1.000000; 1.000000;,
    100; 1.000000; 1.000000; 1.000000; 1.000000;,
    101; 1.000000; 1.000000; 1.000000; 1.000000;,
    102; 1.000000; 1.000000; 1.000000; 1.000000;,
    103; 1.000000; 1.000000; 1.000000; 1.000000;,
    104; 1.000000; 1.000000; 1.000000; 1.000000;,
    105; 1.000000; 1.000000; 1.000000; 1.000000;,
    106; 1.000000; 1.000000; 1.000000; 1.000000;,
    107; 1.000000; 1.000000; 1.000000; 1.000000;,
    108; 1.000000; 1.000000; 1.000000; 1.000000;,
    109; 1.000000; 1.000000; 1.000000; 1.000000;,
    110; 1.000000; 1.000000; 1.000000; 1.000000;,
    111; 1.000000; 1.000000; 1.000000; 1.000000;,
    112; 1.000000; 1.000000; 1.000000; 1.000000;,
    113; 1.000000; 1.000000; 1.000000; 1.000000;;
   }

   MeshMaterialList {
    1;
    72;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material Texture_Launcher_Rocket {
     0.588000; 0.588000; 0.588000; 1.000000;;
     128.000000;
     0.000000; 0.000000; 0.000000;;
     0.000000; 0.000000; 0.000000;;

     TextureFilename {
      "Launcher_rocket_diff.TGA";
     }
    }

   }
  }
}
