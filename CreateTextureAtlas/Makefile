OUT = Release_Linux
CreateTextureAtlas_Linux: CreateTextureAtlas/CreateTextureAtlas.cpp CreateTextureAtlas/PicturesPath.cpp  CreateTextureAtlas/PictureOperation.cpp
	gcc -o Release_Linux/CreateTextureAtlas_Linux CreateTextureAtlas/CreateTextureAtlas.cpp CreateTextureAtlas/PicturesPath.cpp  CreateTextureAtlas/PictureOperation.cpp -lboost_filesystem -ljpeg -lboost_system -lstdc++
$(OUT)/:
	mkdir -p $@

