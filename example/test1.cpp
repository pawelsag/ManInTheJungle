STATES globalState = STATES::ACTIVE;
	SDL_Window *window = nullptr;
	SDL_Renderer * renderObj = nullptr;
	SDL_Texture * textureObj = nullptr;
	SDL_Event e;

	std::string fileName("plx-1.png");
	globalState = STATES::ACTIVE;
	window = SDL_CreateWindow("SDL Test", 0, 20, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
	if(window == NULL){
		printf("Getting window failed\n");
		return 1;
	}

	renderObj = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	if (renderObj == NULL)
	{
		printf("Renderer failed\n");
		return 2;
	}
	SDL_SetRenderDrawColor(renderObj, 0xff,0xff,0xff,0xff);

	if( !(IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG) ){
		printf("Img init failed\n");
		return 3;
	}
	
	SDL_RenderClear( renderObj );
	for(int i = 1 ; i < 6 ; i++){
		fileName[4] = (char)(i + 0x30);
		printf("%s\n",(std::string(pathToBG) + fileName).c_str() );
		SDL_Surface *loadedSurface = IMG_Load((std::string(pathToBG) + fileName).c_str());
		
		textureObj = SDL_CreateTextureFromSurface(renderObj,loadedSurface);
		if( textureObj == NULL ){
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
			return 4;
		}
		SDL_FreeSurface(loadedSurface);
		SDL_RenderCopy( renderObj, textureObj, NULL, NULL);
	}
	SDL_Surface *loadedSurface = IMG_Load((std::string(pathToBG) + std::string("sprites.png") ).c_str());
	textureObj = SDL_CreateTextureFromSurface(renderObj,loadedSurface);
	SDL_FreeSurface(loadedSurface);

	SDL_Rect positionText = { 0, 0, 100, 100 };
	for(globalCameraVelocity=0 ; globalCameraVelocity < 100; globalCameraVelocity++ ){
		positionText.x = globalCameraVelocity;		
		SDL_RenderCopy( renderObj, textureObj, NULL, &positionText);
		SDL_RenderPresent( renderObj );
		printf("%i\n", globalCameraVelocity);
		Sleep(50);
	}
	
	while(globalState != STATES::QUIT){
		while(SDL_PollEvent( &e ) != 0){
			if(e.type == SDL_QUIT){
				globalState = STATES::QUIT;
			}
		}
	}
