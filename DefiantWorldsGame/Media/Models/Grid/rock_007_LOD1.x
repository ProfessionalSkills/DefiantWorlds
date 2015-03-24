xof 0303txt 0032

// DirectX 9.0 file
// Creator: Ultimate Unwrap3D Pro v3.22
// Website: http://www.unwrap3d.com
// Time: Fri Mar 12 16:53:48 2010

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

Frame rock_007_LOD1 {
   FrameTransformMatrix {
    1.000000, 0.000000, 0.000000, 0.000000,
    0.000000, 1.000000, 0.000000, 0.000000,
    0.000000, 0.000000, 1.000000, 0.000000,
    0.000000, 0.000000, 0.000000, 1.000000;;
   }

   Mesh rock_007_LOD1 {
    345;
    0.573535; 0.000000; -2.630262;,
    0.790772; 0.377542; -2.744337;,
    0.693769; 0.000000; -3.042689;,
    1.010392; 0.000000; -2.526943;,
    1.069572; 0.000000; -2.931027;,
    0.573535; 0.000000; -2.630262;,
    1.010392; 0.000000; -2.526943;,
    0.693769; 0.000000; -3.042689;,
    -0.524553; 0.003299; 2.059962;,
    0.021687; 0.454633; 2.531497;,
    -0.788538; 0.449022; 2.011267;,
    -0.380058; 0.971045; 1.662194;,
    0.333315; 0.953368; 2.240184;,
    0.242128; 0.960898; 1.162864;,
    -0.058295; 0.449022; 0.996234;,
    0.609132; 0.454633; 1.079568;,
    0.633959; 0.000000; 1.288731;,
    -0.203877; 0.001138; 1.237268;,
    1.405765; 0.006525; 1.918705;,
    1.643805; 0.488296; 1.764055;,
    1.527910; 0.368086; 2.259208;,
    -0.203877; 0.001138; 1.237268;,
    -0.596027; 0.453797; 1.346855;,
    -0.058295; 0.449022; 0.996234;,
    0.910559; 0.747157; 2.444699;,
    1.455276; 0.801801; 1.891973;,
    1.643805; 0.488296; 1.764055;,
    1.405765; 0.006525; 1.918705;,
    1.031762; 0.000000; 2.537475;,
    1.161102; 0.488296; 2.686330;,
    0.910559; 0.747157; 2.444699;,
    -0.380058; 0.971045; 1.662194;,
    1.161102; 0.488296; 2.686330;,
    1.031762; 0.000000; 2.537475;,
    -0.524553; 0.003299; 2.059962;,
    -0.788538; 0.449022; 2.011267;,
    -2.296072; 0.635892; 1.180518;,
    -1.884671; 0.917650; 1.506382;,
    -2.091915; 0.608641; 0.530482;,
    -0.686009; 0.000000; 1.746885;,
    -0.566579; -0.001190; 0.951107;,
    -0.527562; 0.720829; 1.308340;,
    -0.733513; 1.024808; 1.764147;,
    -1.990958; 0.002011; 1.503361;,
    -2.272105; 0.191654; 1.271613;,
    -2.195503; 0.133689; 0.924074;,
    -0.666829; 1.062467; 1.236803;,
    -1.955186; 0.065432; 0.587771;,
    -0.777128; 0.464577; 0.707734;,
    -0.566579; -0.001190; 0.951107;,
    -0.499186; 0.661096; 0.938625;,
    -1.181558; 0.029169; 1.865454;,
    -0.686009; 0.000000; 1.746885;,
    -0.733513; 1.024808; 1.764147;,
    -0.702983; 0.900729; 0.766460;,
    -1.990958; 0.002011; 1.503361;,
    -2.272105; 0.191654; 1.271613;,
    -1.955186; 0.065432; 0.587771;,
    -0.499186; 0.661096; 0.938625;,
    0.721211; -0.012703; 0.298949;,
    0.409546; 0.789820; -0.359224;,
    0.907390; 0.706070; 0.565804;,
    0.288185; 1.211795; 0.747641;,
    -0.084683; 1.280380; -0.183148;,
    -0.879108; 1.147649; 0.489231;,
    -0.297977; 1.017705; 1.025498;,
    -0.326812; 0.536939; 1.132361;,
    -0.919834; 0.551367; 0.696412;,
    -0.787754; 0.000000; 0.413701;,
    -0.019597; -0.000806; 0.915476;,
    -1.196285; 0.001356; -0.588508;,
    -1.547189; 0.690247; -0.500260;,
    -1.164096; 0.640798; -0.922005;,
    -0.019597; -0.000806; 0.915476;,
    0.371441; 0.602702; 1.090459;,
    -0.326812; 0.536939; 1.132361;,
    -0.509373; 1.085727; -0.714100;,
    -1.326417; 1.051662; -0.477007;,
    -1.547189; 0.690247; -0.500260;,
    -1.196285; 0.001356; -0.588508;,
    -0.504481; 0.000000; -0.980829;,
    -0.598251; 0.842547; -1.112037;,
    -0.509373; 1.085727; -0.714100;,
    0.288185; 1.211795; 0.747641;,
    -0.598251; 0.842547; -1.112037;,
    -0.504481; 0.000000; -0.980829;,
    0.721211; -0.012703; 0.298949;,
    0.907390; 0.706070; 0.565804;,
    2.241794; 0.000000; -1.293570;,
    0.407806; -0.064090; -0.783022;,
    1.479764; 0.119523; -1.801449;,
    2.414772; 0.263108; -1.621791;,
    2.113866; 0.921764; -1.429842;,
    1.252548; 0.722826; -1.678526;,
    1.691923; 1.190300; -0.808231;,
    2.059751; 0.775902; -0.538025;,
    1.402860; 0.808960; -0.397187;,
    1.341456; 0.000000; -0.331846;,
    2.164060; 0.003967; -0.602535;,
    0.407806; -0.064090; -0.783022;,
    0.200674; 0.640532; -0.655218;,
    0.154313; 0.305985; -1.053950;,
    2.164060; 0.003967; -0.602535;,
    2.451238; 0.575514; -1.005675;,
    2.059751; 0.775902; -0.538025;,
    0.653241; 0.504826; -1.574295;,
    0.318082; 0.847143; -0.961352;,
    0.200674; 0.640532; -0.655218;,
    0.407806; -0.064090; -0.783022;,
    0.352800; 0.192033; -1.582204;,
    0.653241; 0.504826; -1.574295;,
    2.113866; 0.921764; -1.429842;,
    0.352800; 0.192033; -1.582204;,
    2.241794; 0.000000; -1.293570;,
    2.414772; 0.263108; -1.621791;,
    3.569617; 0.802531; 0.452043;,
    3.437531; 0.905321; -0.119633;,
    3.066186; 0.896905; 0.821159;,
    3.000151; 0.412329; 0.922280;,
    2.628166; 0.873630; 0.586801;,
    2.871910; 0.005115; 0.788018;,
    2.631261; 0.000000; -0.820480;,
    2.148092; 0.017574; -0.475245;,
    2.677843; 0.720128; -1.001813;,
    3.554076; 0.005658; 0.315086;,
    3.608068; 0.354077; 0.512300;,
    3.337192; 0.371822; 0.749622;,
    2.303858; 0.868861; -0.658372;,
    2.093077; 0.025654; 0.000501;,
    1.992221; 0.530870; -0.399996;,
    2.148092; 0.017574; -0.475245;,
    3.058403; 0.013045; -0.603337;,
    2.631261; 0.000000; -0.820480;,
    2.677843; 0.720128; -1.001813;,
    2.049072; 0.841757; -0.230540;,
    3.554076; 0.005658; 0.315086;,
    3.608068; 0.354077; 0.512300;,
    3.000151; 0.412329; 0.922280;,
    2.871910; 0.005115; 0.788018;,
    1.992221; 0.530870; -0.399996;,
    0.749454; -0.012703; 0.007002;,
    0.749551; 0.789820; 0.735237;,
    0.695351; 0.706070; -0.313853;,
    1.332818; 1.211794; -0.213276;,
    1.271592; 1.280380; 0.787550;,
    2.277312; 1.147649; 0.519717;,
    1.981502; 1.017705; -0.213626;,
    2.053286; 0.536939; -0.297877;,
    2.402766; 0.551367; 0.349881;,
    2.162426; 0.000000; 0.548898;,
    1.682815; -0.000806; -0.233286;,
    2.102878; 0.001356; 1.629534;,
    2.457800; 0.690247; 1.699906;,
    1.931097; 0.640798; 1.917195;,
    1.682815; -0.000806; -0.233286;,
    1.404243; 0.602702; -0.558753;,
    2.053286; 0.536939; -0.297877;,
    1.428279; 1.085727; 1.449154;,
    2.268204; 1.051662; 1.584433;,
    2.457800; 0.690247; 1.699906;,
    2.102878; 0.001356; 1.629534;,
    1.309736; 0.000000; 1.688143;,
    1.338353; 0.842547; 1.846854;,
    1.428279; 1.085727; 1.449154;,
    1.332818; 1.211794; -0.213276;,
    1.338353; 0.842547; 1.846854;,
    1.309736; 0.000000; 1.688143;,
    0.749454; -0.012703; 0.007002;,
    0.695351; 0.706070; -0.313853;,
    -1.237935; 1.745566; -0.549894;,
    -0.913012; 1.371156; -0.219637;,
    -1.920601; 1.617845; -0.399213;,
    -0.768599; 1.240100; 1.060893;,
    -1.239551; 1.526494; 1.203685;,
    -1.574697; 1.073834; 1.122777;,
    -1.831714; 2.314481; 0.125649;,
    -0.994863; 2.264014; 0.022714;,
    -1.232513; 2.173161; -0.377171;,
    -0.745359; 0.911341; 0.757329;,
    -1.520519; 0.791206; 0.863601;,
    -1.932908; 2.068787; -0.202508;,
    -1.866295; 1.038802; 0.634539;,
    -1.721184; 1.526513; 1.117810;,
    -0.705571; 1.747994; 0.732539;,
    -1.574697; 1.073834; 1.122777;,
    -1.237935; 1.745566; -0.549894;,
    -1.920601; 1.617845; -0.399213;,
    -1.920601; 1.617845; -0.399213;,
    -1.520519; 0.791206; 0.863601;,
    -0.768599; 1.240100; 1.060893;,
    -1.520519; 0.791206; 0.863601;,
    -0.745359; 0.911341; 0.757329;,
    -1.232513; 2.173161; -0.377171;,
    -1.932908; 2.068787; -0.202508;,
    -1.866295; 1.038802; 0.634539;,
    -1.339670; -0.012703; -0.181285;,
    -1.651335; 0.789820; -0.839459;,
    -1.153490; 0.706070; 0.085570;,
    -1.772695; 1.211794; 0.267407;,
    -2.145563; 1.280381; -0.663385;,
    -2.939988; 1.147649; 0.008995;,
    -2.358858; 1.017705; 0.545264;,
    -2.387692; 0.536939; 0.652125;,
    -2.980715; 0.551367; 0.216177;,
    -2.848634; 0.000000; -0.066535;,
    -2.080479; -0.000806; 0.435240;,
    -3.257164; 0.001356; -1.068745;,
    -3.608069; 0.690247; -0.980494;,
    -3.224977; 0.640798; -1.402242;,
    -2.080479; -0.000806; 0.435240;,
    -1.689440; 0.602702; 0.610223;,
    -2.387692; 0.536939; 0.652125;,
    -2.570254; 1.085727; -1.194336;,
    -3.387297; 1.051662; -0.957244;,
    -3.608069; 0.690247; -0.980494;,
    -3.257164; 0.001356; -1.068745;,
    -2.565361; 0.000000; -1.461065;,
    -2.659131; 0.842547; -1.592273;,
    -2.570254; 1.085727; -1.194336;,
    -1.772695; 1.211794; 0.267407;,
    -2.659131; 0.842547; -1.592273;,
    -2.565361; 0.000000; -1.461065;,
    -1.339670; -0.012703; -0.181285;,
    -1.153490; 0.706070; 0.085570;,
    0.176085; 0.019717; -2.543397;,
    -0.772826; 0.407261; -2.606450;,
    0.234405; 0.600381; -2.848792;,
    0.023962; 1.275028; -2.433101;,
    -0.942747; 1.034362; -2.300209;,
    -0.561141; 1.407741; -1.396998;,
    0.145024; 1.374285; -1.774348;,
    0.392214; 1.009538; -1.552439;,
    -0.190188; 0.988339; -1.102666;,
    0.063535; -0.014819; -1.243526;,
    -1.281381; 0.014710; -0.973875;,
    -1.498088; 0.760764; -0.815459;,
    -1.730049; 0.440750; -1.228813;,
    0.063535; -0.014819; -1.243526;,
    0.559306; 0.870457; -2.220550;,
    0.392214; 1.009538; -1.552439;,
    -1.484082; 0.748217; -1.946317;,
    -1.527827; 1.028110; -1.143399;,
    -1.498088; 0.760764; -0.815459;,
    -1.281381; 0.014710; -0.973875;,
    -1.418527; 0.000000; -1.679664;,
    -1.782647; 0.390654; -1.854687;,
    -1.484082; 0.748217; -1.946317;,
    0.023962; 1.275028; -2.433101;,
    -1.782647; 0.390654; -1.854687;,
    -1.418527; 0.000000; -1.679664;,
    0.176085; 0.019717; -2.543397;,
    0.234405; 0.600381; -2.848792;,
    -0.429798; 1.401336; -0.949614;,
    -0.243175; 1.538504; -0.108569;,
    0.040590; 2.023861; -0.381649;,
    -0.206287; 1.817532; -1.289182;,
    0.496700; 1.885300; -1.245708;,
    0.690889; 2.072731; -0.455353;,
    1.119402; 1.317061; -1.099044;,
    0.783551; 0.906018; -1.184700;,
    0.584785; 0.647765; -0.383496;,
    0.180670; 0.780288; -1.071043;,
    0.764759; 0.968227; 0.549625;,
    1.350474; 1.141581; 0.471083;,
    0.981903; 1.446306; 0.681695;,
    0.180670; 0.780288; -1.071043;,
    0.267339; 1.368142; -1.528991;,
    0.783551; 0.906018; -1.184700;,
    0.797225; 1.961682; 0.172278;,
    1.397112; 1.480156; 0.288373;,
    1.350474; 1.141581; 0.471083;,
    0.764759; 0.968227; 0.549625;,
    0.259208; 1.456144; 0.589802;,
    0.660492; 1.913216; 0.581083;,
    0.797225; 1.961682; 0.172278;,
    0.496700; 1.885300; -1.245708;,
    0.660492; 1.913216; 0.581083;,
    0.259208; 1.456144; 0.589802;,
    0.584785; 0.647765; -0.383496;,
    0.764759; 0.968227; 0.549625;,
    0.180670; 0.780288; -1.071043;,
    -0.429798; 1.401336; -0.949614;,
    -0.206287; 1.817532; -1.289182;,
    0.111641; 0.877505; 0.355545;,
    -0.231829; 0.879845; 0.503844;,
    0.136054; 1.241149; 0.201955;,
    0.074340; 1.701124; 0.257809;,
    -0.619502; 1.697828; 0.702111;,
    0.570079; 1.857076; 0.628802;,
    0.731363; 1.316194; 0.593319;,
    0.203565; 0.953428; 1.713999;,
    0.663906; 1.003922; 0.784857;,
    -0.867367; 1.168047; 1.563611;,
    -0.383241; 0.937996; 1.752678;,
    -0.493229; 1.344358; 1.839069;,
    0.111641; 0.877505; 0.355545;,
    0.136054; 1.241149; 0.201955;,
    0.731363; 1.316194; 0.593319;,
    -0.618636; 1.691107; 1.571355;,
    0.186967; 1.680913; 1.788555;,
    -0.231829; 0.879845; 0.503844;,
    0.152722; 0.824571; 0.785955;,
    -0.234393; 0.847598; 1.470002;,
    -0.679716; 0.914437; 1.052352;,
    0.203565; 0.953428; 1.713999;,
    0.186967; 1.680913; 1.788555;,
    -0.109129; 1.274423; 1.721791;,
    -0.383241; 0.937996; 1.752678;,
    -0.867367; 1.168047; 1.563611;,
    -0.679716; 0.914437; 1.052352;,
    -0.679716; 0.914437; 1.052352;,
    0.663906; 1.003922; 0.784857;,
    0.111641; 0.877505; 0.355545;,
    -0.109129; 1.274423; 1.721791;,
    -0.493229; 1.344358; 1.839069;,
    -0.383241; 0.937996; 1.752678;,
    3.276966; 0.000000; 1.781083;,
    3.272712; 0.000000; 1.443241;,
    3.175819; 0.267805; 1.716384;,
    2.878768; 0.000000; 1.408581;,
    3.074150; 0.241006; 1.477630;,
    3.272712; 0.000000; 1.443241;,
    2.879154; 0.000000; 1.817684;,
    3.276966; 0.000000; 1.781083;,
    2.878768; 0.000000; 1.408581;,
    2.879154; 0.000000; 1.817684;,
    -2.147652; -0.000000; 2.757429;,
    -1.974911; 0.371758; 2.931929;,
    -1.718581; -0.000000; 2.752941;,
    -2.117735; -0.000000; 3.205130;,
    -1.714539; 0.000000; 3.143525;,
    -2.147652; -0.000000; 2.757429;,
    -2.117735; -0.000000; 3.205130;,
    -1.718581; -0.000000; 2.752941;,
    -1.204111; 0.068739; 1.725733;,
    -0.803367; 0.047767; 2.121085;,
    -1.014673; 0.354870; 1.835680;,
    -0.777068; 0.379264; 1.555532;,
    -1.204111; 0.068739; 1.725733;,
    -0.684880; 0.440636; 1.810800;,
    -0.377795; 0.034936; 1.742745;,
    -0.803367; 0.047767; 2.121085;,
    -0.806588; 0.045379; 1.329409;,
    -0.377795; 0.034936; 1.742745;,
    -0.806588; 0.045379; 1.329409;;
    342;
    3;0, 1, 2;,
    3;1, 3, 4;,
    3;5, 6, 1;,
    3;4, 7, 1;,
    3;8, 9, 10;,
    3;11, 12, 13;,
    3;14, 15, 16;,
    3;14, 16, 17;,
    3;18, 19, 20;,
    3;21, 22, 23;,
    3;12, 24, 25;,
    3;12, 25, 13;,
    3;16, 15, 26;,
    3;16, 26, 27;,
    3;9, 8, 28;,
    3;9, 28, 29;,
    3;13, 15, 14;,
    3;26, 15, 13;,
    3;26, 13, 25;,
    3;30, 19, 25;,
    3;23, 22, 11;,
    3;23, 11, 13;,
    3;10, 9, 12;,
    3;10, 12, 31;,
    3;24, 12, 9;,
    3;24, 9, 29;,
    3;32, 20, 30;,
    3;33, 18, 20;,
    3;33, 20, 32;,
    3;22, 21, 34;,
    3;22, 34, 35;,
    3;11, 22, 35;,
    3;30, 20, 19;,
    3;36, 37, 38;,
    3;39, 40, 41;,
    3;39, 41, 42;,
    3;43, 44, 45;,
    3;37, 42, 46;,
    3;47, 48, 49;,
    3;49, 48, 50;,
    3;51, 52, 53;,
    3;45, 44, 36;,
    3;45, 36, 38;,
    3;48, 47, 38;,
    3;48, 38, 54;,
    3;50, 48, 54;,
    3;42, 41, 46;,
    3;37, 55, 51;,
    3;37, 51, 42;,
    3;56, 55, 37;,
    3;56, 37, 36;,
    3;57, 45, 38;,
    3;57, 43, 45;,
    3;41, 40, 58;,
    3;46, 41, 58;,
    3;46, 58, 54;,
    3;37, 46, 54;,
    3;37, 54, 38;,
    3;59, 60, 61;,
    3;62, 63, 64;,
    3;62, 64, 65;,
    3;66, 67, 68;,
    3;66, 68, 69;,
    3;70, 71, 72;,
    3;73, 74, 75;,
    3;63, 76, 77;,
    3;63, 77, 64;,
    3;68, 67, 78;,
    3;68, 78, 79;,
    3;60, 59, 80;,
    3;60, 80, 81;,
    3;65, 64, 67;,
    3;65, 67, 66;,
    3;78, 67, 64;,
    3;78, 64, 77;,
    3;82, 71, 77;,
    3;75, 74, 62;,
    3;75, 62, 65;,
    3;61, 60, 63;,
    3;61, 63, 83;,
    3;76, 63, 60;,
    3;76, 60, 81;,
    3;84, 72, 82;,
    3;85, 70, 72;,
    3;85, 72, 84;,
    3;74, 73, 86;,
    3;74, 86, 87;,
    3;62, 74, 87;,
    3;82, 72, 71;,
    3;88, 89, 90;,
    3;88, 90, 91;,
    3;92, 93, 94;,
    3;95, 96, 97;,
    3;95, 97, 98;,
    3;99, 100, 101;,
    3;102, 103, 104;,
    3;93, 105, 106;,
    3;93, 106, 94;,
    3;97, 96, 107;,
    3;97, 107, 108;,
    3;90, 89, 109;,
    3;94, 96, 95;,
    3;107, 96, 94;,
    3;107, 94, 106;,
    3;110, 100, 106;,
    3;104, 103, 92;,
    3;104, 92, 94;,
    3;91, 90, 93;,
    3;91, 93, 111;,
    3;105, 93, 90;,
    3;105, 90, 109;,
    3;112, 101, 110;,
    3;99, 101, 112;,
    3;103, 102, 113;,
    3;103, 113, 114;,
    3;92, 103, 114;,
    3;110, 101, 100;,
    3;115, 116, 117;,
    3;118, 119, 120;,
    3;121, 122, 123;,
    3;124, 125, 126;,
    3;116, 123, 127;,
    3;120, 119, 128;,
    3;128, 129, 130;,
    3;131, 132, 133;,
    3;126, 125, 115;,
    3;126, 115, 117;,
    3;117, 119, 118;,
    3;128, 119, 134;,
    3;129, 128, 134;,
    3;123, 122, 127;,
    3;116, 135, 131;,
    3;116, 131, 123;,
    3;136, 135, 116;,
    3;136, 116, 115;,
    3;137, 126, 117;,
    3;138, 124, 126;,
    3;138, 126, 137;,
    3;127, 122, 139;,
    3;127, 139, 134;,
    3;116, 127, 134;,
    3;116, 134, 119;,
    3;117, 116, 119;,
    3;140, 141, 142;,
    3;143, 144, 145;,
    3;143, 145, 146;,
    3;147, 148, 149;,
    3;147, 149, 150;,
    3;151, 152, 153;,
    3;154, 155, 156;,
    3;144, 157, 158;,
    3;144, 158, 145;,
    3;149, 148, 159;,
    3;149, 159, 160;,
    3;141, 140, 161;,
    3;141, 161, 162;,
    3;146, 145, 148;,
    3;146, 148, 147;,
    3;159, 148, 145;,
    3;159, 145, 158;,
    3;163, 152, 158;,
    3;156, 155, 143;,
    3;156, 143, 146;,
    3;142, 141, 144;,
    3;142, 144, 164;,
    3;157, 144, 141;,
    3;157, 141, 162;,
    3;165, 153, 163;,
    3;166, 151, 153;,
    3;166, 153, 165;,
    3;155, 154, 167;,
    3;155, 167, 168;,
    3;143, 155, 168;,
    3;163, 153, 152;,
    3;169, 170, 171;,
    3;172, 173, 174;,
    3;175, 176, 177;,
    3;170, 178, 179;,
    3;175, 180, 181;,
    3;175, 181, 182;,
    3;176, 175, 173;,
    3;176, 173, 183;,
    3;182, 181, 184;,
    3;183, 173, 172;,
    3;177, 185, 186;,
    3;181, 180, 187;,
    3;184, 181, 188;,
    3;189, 174, 190;,
    3;189, 190, 191;,
    3;178, 183, 172;,
    3;170, 176, 183;,
    3;170, 183, 178;,
    3;192, 176, 170;,
    3;192, 170, 169;,
    3;193, 177, 186;,
    3;175, 177, 193;,
    3;173, 175, 182;,
    3;174, 173, 182;,
    3;170, 179, 194;,
    3;170, 194, 171;,
    3;195, 196, 197;,
    3;198, 199, 200;,
    3;198, 200, 201;,
    3;202, 203, 204;,
    3;202, 204, 205;,
    3;206, 207, 208;,
    3;209, 210, 211;,
    3;199, 212, 213;,
    3;199, 213, 200;,
    3;204, 203, 214;,
    3;204, 214, 215;,
    3;196, 195, 216;,
    3;196, 216, 217;,
    3;201, 200, 203;,
    3;201, 203, 202;,
    3;214, 203, 200;,
    3;214, 200, 213;,
    3;218, 207, 213;,
    3;211, 210, 198;,
    3;211, 198, 201;,
    3;197, 196, 199;,
    3;197, 199, 219;,
    3;212, 199, 196;,
    3;212, 196, 217;,
    3;220, 208, 218;,
    3;221, 206, 208;,
    3;221, 208, 220;,
    3;210, 209, 222;,
    3;210, 222, 223;,
    3;198, 210, 223;,
    3;218, 208, 207;,
    3;224, 225, 226;,
    3;227, 228, 229;,
    3;227, 229, 230;,
    3;231, 232, 233;,
    3;234, 235, 236;,
    3;237, 238, 239;,
    3;228, 240, 241;,
    3;228, 241, 229;,
    3;233, 232, 242;,
    3;233, 242, 243;,
    3;225, 224, 244;,
    3;225, 244, 245;,
    3;230, 229, 232;,
    3;230, 232, 231;,
    3;242, 232, 229;,
    3;242, 229, 241;,
    3;246, 235, 241;,
    3;239, 238, 227;,
    3;239, 227, 230;,
    3;226, 225, 228;,
    3;226, 228, 247;,
    3;240, 228, 225;,
    3;240, 225, 245;,
    3;248, 236, 246;,
    3;249, 234, 236;,
    3;249, 236, 248;,
    3;238, 237, 250;,
    3;238, 250, 251;,
    3;227, 238, 251;,
    3;246, 236, 235;,
    3;252, 253, 254;,
    3;252, 254, 255;,
    3;256, 257, 258;,
    3;259, 260, 261;,
    3;262, 263, 264;,
    3;265, 266, 267;,
    3;257, 268, 269;,
    3;257, 269, 258;,
    3;260, 259, 270;,
    3;260, 270, 271;,
    3;254, 253, 272;,
    3;254, 272, 273;,
    3;258, 266, 256;,
    3;270, 259, 258;,
    3;270, 258, 269;,
    3;274, 263, 269;,
    3;267, 266, 258;,
    3;255, 254, 257;,
    3;255, 257, 275;,
    3;268, 257, 254;,
    3;268, 254, 273;,
    3;276, 264, 274;,
    3;277, 262, 264;,
    3;277, 264, 276;,
    3;253, 278, 279;,
    3;253, 279, 272;,
    3;280, 278, 253;,
    3;280, 253, 252;,
    3;266, 265, 281;,
    3;266, 281, 282;,
    3;266, 282, 256;,
    3;274, 264, 263;,
    3;283, 284, 285;,
    3;286, 287, 288;,
    3;289, 290, 291;,
    3;292, 293, 294;,
    3;295, 296, 297;,
    3;287, 298, 288;,
    3;290, 289, 299;,
    3;300, 301, 302;,
    3;300, 302, 303;,
    3;304, 305, 306;,
    3;303, 302, 307;,
    3;303, 307, 308;,
    3;297, 296, 286;,
    3;297, 286, 288;,
    3;299, 289, 288;,
    3;292, 294, 298;,
    3;287, 309, 292;,
    3;287, 292, 298;,
    3;287, 284, 310;,
    3;285, 284, 287;,
    3;285, 287, 286;,
    3;311, 295, 297;,
    3;291, 290, 301;,
    3;291, 301, 312;,
    3;302, 301, 290;,
    3;302, 290, 313;,
    3;302, 313, 307;,
    3;314, 315, 306;,
    3;298, 314, 306;,
    3;298, 306, 305;,
    3;288, 298, 305;,
    3;316, 317, 318;,
    3;319, 320, 321;,
    3;318, 322, 323;,
    3;324, 325, 320;,
    3;318, 317, 320;,
    3;325, 318, 320;,
    3;326, 327, 328;,
    3;327, 329, 330;,
    3;331, 332, 327;,
    3;330, 333, 327;,
    3;334, 335, 336;,
    3;337, 338, 336;,
    3;337, 336, 339;,
    3;340, 339, 341;,
    3;337, 342, 338;,
    3;343, 344, 337;,
    3;343, 337, 339;,
    3;336, 335, 339;;

   MeshTextureCoords {
    345;
    0.122222; 0.363999;,
    0.086738; 0.323625;,
    0.071604; 0.371362;,
    0.073699; 0.277981;,
    0.046670; 0.316599;,
    0.131723; 0.318625;,
    0.099095; 0.268700;,
    0.058186; 0.361481;,
    0.605667; 0.992046;,
    0.649361; 0.943220;,
    0.572978; 0.951115;,
    0.579182; 0.877813;,
    0.654747; 0.894299;,
    0.615641; 0.816866;,
    0.589532; 0.772554;,
    0.644366; 0.776617;,
    0.659200; 0.736752;,
    0.599471; 0.729846;,
    0.799026; 0.840239;,
    0.754875; 0.818246;,
    0.762986; 0.857868;,
    0.506621; 0.805543;,
    0.537429; 0.846739;,
    0.556935; 0.797197;,
    0.707802; 0.895086;,
    0.725859; 0.828683;,
    0.739171; 0.799653;,
    0.734513; 0.752872;,
    0.736149; 0.962849;,
    0.736062; 0.915070;,
    0.714903; 0.891632;,
    0.584683; 0.895823;,
    0.750388; 0.900434;,
    0.797246; 0.899405;,
    0.476131; 0.872031;,
    0.515463; 0.898818;,
    0.217250; 0.510619;,
    0.224971; 0.563267;,
    0.296087; 0.497792;,
    0.283985; 0.754970;,
    0.343476; 0.732283;,
    0.301001; 0.679221;,
    0.245074; 0.668976;,
    0.164690; 0.363967;,
    0.180234; 0.448227;,
    0.241935; 0.427742;,
    0.290797; 0.645721;,
    0.359250; 0.483528;,
    0.364450; 0.603077;,
    0.414486; 0.614905;,
    0.357434; 0.642980;,
    0.149864; 0.630902;,
    0.150921; 0.679257;,
    0.238013; 0.664213;,
    0.329294; 0.625037;,
    0.144407; 0.545257;,
    0.169159; 0.509837;,
    0.308879; 0.393088;,
    0.336163; 0.667612;,
    0.212988; 0.681505;,
    0.177819; 0.757875;,
    0.261800; 0.734477;,
    0.270404; 0.813635;,
    0.180214; 0.813540;,
    0.197261; 0.899389;,
    0.265289; 0.892992;,
    0.275124; 0.939942;,
    0.212349; 0.944664;,
    0.202487; 0.997506;,
    0.271112; 0.994226;,
    0.015791; 0.901960;,
    0.079892; 0.916881;,
    0.063853; 0.873249;,
    0.405248; 0.900972;,
    0.341265; 0.842872;,
    0.321760; 0.921431;,
    0.120125; 0.821505;,
    0.111044; 0.899936;,
    0.100995; 0.935133;,
    0.115106; 0.996931;,
    0.070670; 0.732897;,
    0.084938; 0.803598;,
    0.112605; 0.826605;,
    0.259164; 0.798798;,
    0.070712; 0.822642;,
    0.001353; 0.836043;,
    0.446961; 0.793078;,
    0.361320; 0.753244;,
    0.160764; 0.188450;,
    0.197509; 0.297856;,
    0.205694; 0.233337;,
    0.192287; 0.168724;,
    0.256416; 0.166681;,
    0.248039; 0.233954;,
    0.314557; 0.194371;,
    0.349323; 0.169257;,
    0.348171; 0.216135;,
    0.399001; 0.228444;,
    0.402295; 0.177633;,
    0.289682; 0.358170;,
    0.321631; 0.314276;,
    0.288075; 0.324354;,
    0.314702; 0.077133;,
    0.282416; 0.124379;,
    0.331105; 0.138572;,
    0.251521; 0.279637;,
    0.310343; 0.290054;,
    0.336510; 0.299110;,
    0.384247; 0.293081;,
    0.236513; 0.305344;,
    0.255102; 0.285569;,
    0.240678; 0.173675;,
    0.250361; 0.316919;,
    0.255539; 0.074083;,
    0.231165; 0.107584;,
    0.409058; 0.328834;,
    0.403737; 0.374596;,
    0.472187; 0.330119;,
    0.522395; 0.328040;,
    0.486495; 0.371541;,
    0.558125; 0.349442;,
    0.408151; 0.530283;,
    0.458822; 0.527635;,
    0.398607; 0.467332;,
    0.408066; 0.229702;,
    0.405505; 0.276762;,
    0.445503; 0.276654;,
    0.441613; 0.457746;,
    0.544250; 0.439947;,
    0.498192; 0.468832;,
    0.544163; 0.467774;,
    0.336239; 0.422472;,
    0.334264; 0.462893;,
    0.393994; 0.462133;,
    0.478107; 0.448247;,
    0.336316; 0.336362;,
    0.369279; 0.317013;,
    0.487900; 0.280153;,
    0.493837; 0.229318;,
    0.475358; 0.485244;,
    0.727567; 0.686191;,
    0.790955; 0.718512;,
    0.773998; 0.646730;,
    0.845749; 0.643294;,
    0.838109; 0.718333;,
    0.911230; 0.706671;,
    0.907996; 0.648980;,
    0.947913; 0.642161;,
    0.949969; 0.695331;,
    0.994328; 0.705277;,
    0.993619; 0.647201;,
    0.907564; 0.860173;,
    0.922266; 0.806494;,
    0.884874; 0.818636;,
    0.913696; 0.554261;,
    0.872926; 0.595945;,
    0.926853; 0.610297;,
    0.842887; 0.769439;,
    0.908961; 0.779615;,
    0.938445; 0.789215;,
    0.991172; 0.779178;,
    0.766205; 0.808315;,
    0.826533; 0.798628;,
    0.847003; 0.775947;,
    0.828543; 0.651250;,
    0.842330; 0.811208;,
    0.851405; 0.870227;,
    0.843923; 0.524718;,
    0.815887; 0.579441;,
    0.139193; 0.169218;,
    0.109893; 0.165365;,
    0.137740; 0.202794;,
    0.047871; 0.134516;,
    0.054374; 0.095535;,
    0.024950; 0.078907;,
    0.133067; 0.061537;,
    0.128813; 0.123311;,
    0.189634; 0.107324;,
    0.056820; 0.161162;,
    0.053153; 0.200861;,
    0.136029; 0.030131;,
    0.053276; 0.027791;,
    0.056511; 0.068155;,
    0.079770; 0.125992;,
    0.033227; 0.054445;,
    0.234775; 0.093628;,
    0.218720; 0.041059;,
    0.115382; 0.003562;,
    0.029802; 0.033791;,
    0.040123; 0.129264;,
    0.001876; 0.086318;,
    0.010071; 0.131773;,
    0.148806; 0.142627;,
    0.166139; 0.043068;,
    0.071350; 0.220124;,
    0.526030; 0.520941;,
    0.499405; 0.583720;,
    0.566893; 0.562666;,
    0.574997; 0.627214;,
    0.502736; 0.628800;,
    0.518778; 0.697943;,
    0.573720; 0.690983;,
    0.582916; 0.728721;,
    0.532205; 0.734231;,
    0.525643; 0.777310;,
    0.581136; 0.772776;,
    0.371751; 0.704765;,
    0.424090; 0.715206;,
    0.409960; 0.680260;,
    0.701802; 0.713347;,
    0.640237; 0.652710;,
    0.619441; 0.723351;,
    0.454199; 0.636786;,
    0.448895; 0.700660;,
    0.441683; 0.729478;,
    0.454787; 0.779210;,
    0.411908; 0.566086;,
    0.425204; 0.623103;,
    0.448241; 0.641167;,
    0.566348; 0.614846;,
    0.414206; 0.639073;,
    0.358360; 0.651714;,
    0.757822; 0.604741;,
    0.653406; 0.560156;,
    0.613736; 0.308940;,
    0.628019; 0.379572;,
    0.671277; 0.314841;,
    0.725770; 0.367668;,
    0.662375; 0.415610;,
    0.723812; 0.463110;,
    0.766165; 0.419822;,
    0.799532; 0.446518;,
    0.759644; 0.484140;,
    0.815264; 0.530194;,
    0.600995; 0.567041;,
    0.656190; 0.543536;,
    0.619754; 0.523972;,
    0.882501; 0.355467;,
    0.779686; 0.357150;,
    0.808131; 0.405261;,
    0.627013; 0.456272;,
    0.667008; 0.513939;,
    0.681147; 0.543183;,
    0.727139; 0.581027;,
    0.557521; 0.434132;,
    0.593019; 0.465025;,
    0.624977; 0.464119;,
    0.707017; 0.359929;,
    0.594763; 0.486043;,
    0.566623; 0.523255;,
    0.815535; 0.289278;,
    0.758022; 0.302110;,
    0.702840; 0.197725;,
    0.684425; 0.138365;,
    0.648285; 0.154789;,
    0.662915; 0.223678;,
    0.600994; 0.223673;,
    0.603785; 0.150225;,
    0.522474; 0.187899;,
    0.482510; 0.202799;,
    0.443757; 0.141111;,
    0.437200; 0.202483;,
    0.560013; 0.004764;,
    0.531452; 0.048751;,
    0.571485; 0.041924;,
    0.511905; 0.314536;,
    0.557232; 0.267111;,
    0.497004; 0.253114;,
    0.606933; 0.099284;,
    0.540982; 0.078211;,
    0.512353; 0.063673;,
    0.466223; 0.066698;,
    0.674925; 0.078036;,
    0.627398; 0.074547;,
    0.603745; 0.091352;,
    0.608716; 0.218276;,
    0.613795; 0.055990;,
    0.614431; 0.005934;,
    0.765407; 0.113814;,
    0.716959; 0.053004;,
    0.764021; 0.178147;,
    0.583502; 0.348583;,
    0.615135; 0.299326;,
    0.839339; 0.293966;,
    0.864170; 0.293390;,
    0.827395; 0.270314;,
    0.833829; 0.236503;,
    0.888905; 0.243127;,
    0.828703; 0.194366;,
    0.804038; 0.161319;,
    0.869478; 0.096852;,
    0.801018; 0.133358;,
    0.950339; 0.235048;,
    0.976673; 0.223839;,
    0.956270; 0.209162;,
    0.771439; 0.248291;,
    0.801003; 0.247669;,
    0.788659; 0.199753;,
    0.930921; 0.210544;,
    0.902173; 0.141269;,
    0.783949; 0.059539;,
    0.800339; 0.090942;,
    0.853880; 0.060686;,
    0.824111; 0.027685;,
    0.958374; 0.111457;,
    0.910606; 0.142246;,
    0.955479; 0.148919;,
    0.876002; 0.046921;,
    0.857735; 0.020765;,
    0.940887; 0.261777;,
    0.913480; 0.283201;,
    0.762175; 0.200911;,
    0.779778; 0.108434;,
    0.871005; 0.070308;,
    0.963094; 0.185995;,
    0.990808; 0.160137;,
    0.049739; 0.575271;,
    0.079485; 0.604682;,
    0.068812; 0.563783;,
    0.114018; 0.560542;,
    0.091257; 0.566455;,
    0.096088; 0.587224;,
    0.063139; 0.531232;,
    0.048649; 0.566015;,
    0.105149; 0.539642;,
    0.073470; 0.527117;,
    0.141612; 0.447945;,
    0.102822; 0.447892;,
    0.121575; 0.484162;,
    0.077043; 0.417525;,
    0.066506; 0.458668;,
    0.128758; 0.419816;,
    0.088569; 0.411594;,
    0.100992; 0.499747;,
    0.023532; 0.794729;,
    0.036127; 0.806041;,
    0.033802; 0.792695;,
    0.036968; 0.782916;,
    0.021504; 0.790300;,
    0.042487; 0.790343;,
    0.058957; 0.794102;,
    0.045173; 0.806148;,
    0.028290; 0.772962;,
    0.060365; 0.772536;,
    0.034854; 0.763316;;
   }

   MeshMaterialList {
    1;
    342;
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

    Material lambert15SG {
     1.000000; 1.000000; 1.000000; 1.000000;;
     128.000000;
     0.050000; 0.050000; 0.050000;;
     0.000000; 0.000000; 0.000000;;

     TextureFilename {
      "rock_007_c.tga";
     }
    }

   }
  }
}
