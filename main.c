#include<SDL2/SDL.h>
#include<SDL2/SDL_hints.h>
#include<SDL2/SDL_error.h>
#include<SDL2/SDL_log.h>
#include<SDL2/SDL_video.h>
#include<SDL2/SDL_render.h>
#include<SDL2/SDL_pixels.h>
#include<SDL2/SDL_rect.h>
#include<SDL2/SDL_surface.h>
#include<SDL2/SDL_clipboard.h>
#include<SDL2/SDL_events.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDl_timer.h>
#include<assert.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<omp.h>
#undef main 
#define width  1500
#define height 800

//#define Nprey 30
#define SEED  10
#define Nfood 1000
#define MutationChance 0.5
#define Nround 10000
size_t Nprey = 15;


typedef struct PREY{
	
	SDL_Point Cordinate;         //Cordinates of PREY
	float Energy;               //How mutch want food
	float Gens[4];  		   //SPEED VISION METABOLISAM SPEED REPRODUCTION SPEED
	SDL_Color col;            //BLUE COLLOR
}PREY;


typedef struct FOOD{
	
	SDL_Point Cordinate;    //Cordinates of food alwayes 30 on  map 
	//SDL_Color col;       GREEN COLLOR
	//size_t time;   // time for spawn of new food on a map
}FOOD;

void RandFood(SDL_Point *food)
{
	if(rand()%8==0){
		food->x = rand()%width;
		food->y = rand()%height;
}
	else
	{
			food->x = rand()%(width-400)+300;
			food->y = rand()%(height-30)+30;
	}

	 
}


void Init(PREY *prey, FOOD *food)           //INIT PRAY,FOOD,PREDATOR 
{
	srand(SEED);
	srand(time(0));
	for(size_t i = 0 ; i < Nfood; i++){
		RandFood(&food[i].Cordinate);
	}
	
	for(size_t i = 0; i < Nprey;i++){
		prey[i].Cordinate.x = rand()%(width);
		prey[i].Cordinate.y = rand()%height;
		prey[i].Energy = 2000+rand()%10000;
		prey[i].col.a=255;
		//5 colors RED GREEN BLUE WHITE YELOW
		if(i%5==0)
	{
		prey[i].col.r = 255;
		prey[i].col.g = 0;
		prey[i].col.b = 0;
	}
		
	if(i%5==1)
	{
		prey[i].col.r = 0;
		prey[i].col.g = 255;
		prey[i].col.b = 0;
	}
	if(i%5==2)
	{
		prey[i].col.r = 0;
		prey[i].col.g = 0;
		prey[i].col.b = 255;
	}
	if(i%5==3)
	{
		prey[i].col.r = 255;
		prey[i].col.g = 255;
		prey[i].col.b = 0;
	}

	if(i%5==4)
	{
		prey[i].col.r = 255;
		prey[i].col.g = 255;
		prey[i].col.b = 255;
	}
		prey[i].Gens[0]=  (float)rand() / RAND_MAX + 0.01;   //ENERGY WHEN GET FOOD
		prey[i].Gens[1] = (float)(rand() % 4)+1;   // SPEED TOWARD FOOD
		prey[i].Gens[2] = (float)(rand() % 5+1);   //How Mutch ofspring get energy
		prey[i].Gens[3] = (float)(rand()%5+1);	
		//prey[i].Gens[3]= 0;       
	}
}

void CheckBoundury(PREY *prey)
{
	for(size_t i = 0; i < Nprey;i++){
		//X axis
		if(prey[i].Cordinate.x < 0){
			prey[i].Cordinate.x = width - 10;	
		}
		if(prey[i].Cordinate.x > width){
			
			prey[i].Cordinate.x = 10;	
		}
		//Y axis
		if(prey[i].Cordinate.y < 0){
			prey[i].Cordinate.y= height-10;
			
		}
		
		if(prey[i].Cordinate.y > height){
			prey[i].Cordinate.y = 10;
		
		}
	
}
}



void MainRenderer(SDL_Renderer *renderer, PREY *prey, FOOD *food)   //RENDERING ON SCREEN
{
	SDL_RenderClear(renderer);
	
	//FOOD

	for(size_t i = 0; i < Nfood; i++){
		SDL_Rect rect;
		rect.h = 5;
		rect.w = 5;
		rect.x = food[i].Cordinate.x;  
		rect.y = food[i].Cordinate.y;
		//printf("x: %d y:%d\n",rect.x,rect.y);
		//system("pause");
		SDL_SetRenderDrawColor(renderer,0,255,0,255);
		SDL_RenderFillRect(renderer,&rect);
	}	
	
	
	//PREY
	for(size_t i = 0; i < Nprey; i++){
		SDL_Rect rect;
		rect.h = 10;
		rect.w = 10;
		rect.x = prey[i].Cordinate.x;  
		rect.y = prey[i].Cordinate.y;
		//printf("x: %d y:%d\n",rect.x,rect.y);
		//system("pause");
		SDL_SetRenderDrawColor(renderer,prey[i].col.r,prey[i].col.g,prey[i].col.b,0);
		SDL_RenderFillRect(renderer,&rect);
		//SDL_Delay(1);
		
	}
	SDL_SetRenderDrawColor(renderer,0,0,0,0);
	SDL_RenderPresent(renderer);
	SDL_Delay(20);
	//system("pause");
	
	
}

int randPN(){
	if(rand()%2==0)
		return rand()%4;
	else 
		return -1*rand()%4;
}


void UpdateStep(PREY *prey, FOOD *food)
{
	//Update prey
	
	//VISION RANGE 20 PIXEL AROUND 
	for(size_t i = 0; i < Nprey; i++){ prey[i].Energy-=(prey[i].Gens[0]+rand()%20);
		int isMove=0;
		for(size_t j = 0; j < Nfood; j++)
		{
			if((food[j].Cordinate.y >= (prey[i].Cordinate.y-20))&&(food[j].Cordinate.y <= (prey[i].Cordinate.y+20)))
			{
				
					if(food[j].Cordinate.x > prey[i].Cordinate.x){
						if(prey[i].Energy>0){
							isMove=1;
							prey[i].Cordinate.x+=prey[i].Gens[1];
							//if(p)
							
							//prey[i].Energy--;
						}
						
					}
						
					if(food[j].Cordinate.x < prey[i].Cordinate.x){
							if(prey[i].Energy>0){
								isMove=1;
							prey[i].Cordinate.x-=prey[i].Gens[1];;
							//prey[i].Energy--;
						}
							
						}
					if(food[j].Cordinate.x >= (prey[i].Cordinate.x-5)&&(food[j].Cordinate.x <= (prey[i].Cordinate.x+5))){
						RandFood(&food[j].Cordinate);
						prey[i].Energy+=2000*prey[i].Gens[0];
					}
						//system("pause");
			}
			
			if(isMove==0)
			{
				if(prey[i].Energy>0){
					
					if(rand()%5 >= prey[i].Gens[3])
						prey[i].Cordinate.y+=randPN();
					else
						prey[i].Cordinate.x+=randPN();
					isMove=0;
				
			}	
			}
			
		
		}	 
		
	}
	//system("pause");
	
	
}


void ReproducePrey(PREY *prey){
	
	for(size_t i = 0; i < Nprey; i++){
		if(prey[i].Energy >= 20000)
		{
			prey[i].Energy-=10000;
			if(Nprey < 300){
				for(size_t j = 0; j < prey[i].Gens[2];j++){
					//memccpy((void*)&prey[Nprey],(void*)&prey[i+j],0,sizeof(PREY));  
					prey[Nprey].Energy = 10000/(prey[i].Gens[2]+1); 
					prey[Nprey].Cordinate.x=prey[i].Cordinate.x;
					prey[Nprey].Cordinate.y=prey[i].Cordinate.y;
					prey[Nprey].col.r=prey[i].col.r;
					prey[Nprey].col.g=prey[i].col.g;
					prey[Nprey].col.b=prey[i].col.b;
					prey[Nprey].Gens[0]=prey[i].Gens[0];
					prey[Nprey].Gens[1]=prey[i].Gens[1];
					prey[Nprey].Gens[2]=prey[i].Gens[2];
					prey[Nprey].Gens[3]=prey[i].Gens[3];
					
					//Mutation
					if((float)rand()/RAND_MAX<=MutationChance){
						srand(time(0));
						int a = rand();
						if(a%4==0){
							prey[i].Gens[0]= (float)rand() / RAND_MAX + 0.4;   //ENERGY WHEN GET FOOD
						}
						if(a%4==1){
							prey[i].Gens[1] =  (float)(rand() % 4);   //SPEED WHEN RUNING FROM PREDATOR							
						}
						if(a%4==2){
							prey[i].Gens[2] = (float)(rand() % 6+1);   //How Mutch ofspring get energy
						}
						if(a%4==3){
							prey[i].Gens[3] = (float)(rand()%4+1);
							
						}
					}
					
						Nprey++;
				}
				printf("Nprey %d\n",Nprey);
			}
		}
	}
	
}

void CheckDeadPrey(PREY *prey){
	for(size_t i = 0; i < Nprey; i++){
		if(prey[i].Energy <= 0)
		{
			for(size_t j = i; j < Nprey-1;j++)
			{
				prey[j].Gens[0]=prey[j+1].Gens[0];
				prey[j].Gens[1]=prey[j+1].Gens[1];
				prey[j].Gens[2]=prey[j+1].Gens[2];
				prey[j].Gens[3]=prey[j+1].Gens[3];
				prey[j].Energy = 10000/(prey[j+1].Gens[2]+1); 
				prey[j].Cordinate.x=prey[j+1].Cordinate.x;
				prey[j].Cordinate.y=prey[j+1].Cordinate.y;
				prey[j].col.r=prey[j+1].col.r;
				prey[j].col.g=prey[j+1].col.g;
				prey[j].col.b=prey[j+1].col.b;
				Nprey--;
				printf("Nprey: %d\n", Nprey);
			}
		}

}
}


int main(){
	
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_CreateWindowAndRenderer(width,height,SDL_RENDERER_ACCELERATED | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,&window,&renderer);
	PREY prey[Nprey+400];
	FOOD food[Nfood];
	Init(&prey,&food);
	int count=0;
	while(1){	
		SDL_Event event;
		while (SDL_PollEvent(&event)) {};
	#pragma omp parallel			
				{
				MainRenderer(renderer,&prey,&food);
				UpdateStep(&prey,&food);
				CheckBoundury(&prey);
				ReproducePrey(&prey);
				CheckDeadPrey(&prey);
				}
				if(count==Nround||Nprey==0)
					break;
				count++;
			}       //w,r,g,b,y
		size_t COL[]={0,0,0,0,0};
		double GENS[]={0.0f,0.0f,0.0f,0.0f};	
		double GENSS[]={0.0f,0.0f,0.0f,0.0f};
		for(size_t i = 0; i < Nprey;i++)
		{
			GENS[0]=prey[i].Gens[0]; 
			GENS[1]=prey[i].Gens[1];
			GENS[2]=prey[i].Gens[2];
			GENS[3]=prey[i].Gens[3];   
			GENSS[0]+=prey[i].Gens[0]; 
			GENSS[1]+=prey[i].Gens[1];
			GENSS[2]+=prey[i].Gens[2];
			GENSS[3]+=prey[i].Gens[3];
			printf("\nGEN 1: %f \nGEN2: %f \nGEN3: %f \nGEN4: %f\n",GENS[0],GENS[1],GENS[2],GENS[3]);
			if(prey[i].col.r==255&&prey[i].col.b==255&&prey[i].col.g==255)
				COL[0]++;
			else if(prey[i].col.g==255&&prey[i].col.r==255)
				COL[4]++;
			else if(prey[i].col.r==255)
				COL[1]++;
			else if(prey[i].col.g==255)
				COL[2]++;
			else if(prey[i].col.b==255)
				COL[3]++;
		}
	//system("pause");
	if(Nprey > 0)
		printf("\nAVR GEN 1: %f \nAVR GEN2: %f \nAVR GEN3: %f \nAVR GEN4: %f\n",(float)GENSS[0]/(float)Nprey,(float)GENSS[1]/(float)Nprey,(float)GENSS[2]/(float)Nprey,(float)GENSS[3]/(float)Nprey);	
	printf("\n\nWHITE: %d\nRED %d\nGRREN: %d\nBLUE: %d\nYELLOW: %d\n",COL[0],COL[1],COL[2],COL[3],COL[4]);
	printf("\nNesto");
	return 0;
}
