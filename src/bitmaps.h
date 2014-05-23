//bitmap enumerations with for reference in drawpreloaded
//and draw bitmap. each enum starts with first one in db 
//that dmresid:

//map bitmaps 
typedef enum mapBmp {
	grass = 0,
	tallgrass,
	lightforest,
	mediumforest,
	jungle,
	airport1,
	airport2,
	runway,
	riverHorizontal,
	riverVertical,
	building1,
	building2,
	factory,
	tank,
	rock,
	ocean,
	heavywaves,
	beach,
	gun1,
	gun2	
}MapBmp;

//aircraft is first to look for in preloaded
typedef enum aircraftBmp{
	spitfireBmp = 0,
	hurricaneBmp,
	p51dBmp,
	yak9Bmp,
	b17Bmp,
	bf109Bmp,
	ju87Bmp,
	me110Bmp,
	fw190Bmp,
	zeroBmp
} AircraftBmp;

typedef enum objBmp{
	munitionsBmp = 10,
	coalplantBmp,
	v2Bmp,
	aagunBmp,
	art88mmBmp,
	howitzersBmp,
	radarstationBmp,
	panzersBmp,
	kingtigersBmp,
	bunkerBmp		
}ObjBmp;

typedef enum objCompleteBmp{
	munitionsCompleteBmp = 20,
	coalplantCompleteBmp,
	v2CompleteBmp,
	aagunCompleteBmp,
	art88mmCompleteBmp,
	howitzersCompleteBmp,
	radarstationCompleteBmp,
	panzersCompleteBmp,
	kingtigersCompleteBmp,
	bunkerCompleteBmp	
}ObjCompleteBmp;

typedef enum explosionBmp{
	mgfire1Bmp = 30,
	mgfire2Bmp,
	rocketfireBmp,
	cannonfireBmp,
	bombexplode1Bmp,
	bombexplode2,
	bombexplode3Bmp,
	rocketexplodeBmp,
	aircraftexplode1Bmp,
	aircraftexplode2Bmp,
	bomberexplodeBmp
}ExplosionBmp;

typedef enum bulletBmp{
	mg8mmBmp = 40,
	mg12mmBmp,
	mg13mmBmp,
	mg16mmBmp,
	cannon20mmBmp,
	mgff20mmBmp,
	rocket21cmBmp,
	cannon30mmBmp,
	bomb200pLBmp,
	bomb500pLBmp,
	bomb1000pLBmp	
}BulletBmp;	

//app bitmaps
typedef enum appBmp{
	menuBackBmp = 48,
	optionsBackBmp,
	newGameBackBmp,
	aircraftCounterBmp,
	damageOdometerBmp,
	bombTargetBmp,
	loadingBmp,
	pausedBmp
}AppBmp;