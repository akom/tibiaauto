// tibiaauto_util.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "tibiaauto_util.h"
#include "tibiaauto_utilfun.h"

#include "MemReader.h"
#include "PackSender.h"
#include "MemConstData.h"
#include "TibiaMapPoint.h"
#include "TibiaMap.h"
#include "TibiaItem.h"
#include "IPCBackPipe.h"
#include "TibiaTile.h"
#include "tileReader.h"
#include "VariableStore.h"
#include "../md5class.h"


#include "MemUtil.h"
#include "TibiaContainer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CTibiaMap tibiaMap;
CMemReader *reader=NULL;

void startMemReader()
{
	if (reader==NULL)
		reader=new CMemReader();
}

extern HANDLE hPipe;


/////////////////////////////////////////////////////////////////////////////
// CTibiaauto_utilApp

BEGIN_MESSAGE_MAP(CTibiaauto_utilApp, CWinApp)
	//{{AFX_MSG_MAP(CTibiaauto_utilApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTibiaauto_utilApp construction

CTibiaauto_utilApp::CTibiaauto_utilApp()
{
	// perform MD5 check on all dlls which are included
	struct dllEntry {
		char *md5result;
		char *dllName;
	} dllEntryTab[] = {		
		{"A3DF77831CFECBA1D88D6B14E9AD955F","tibiaauto.exe"}
	};
		
	
	CMD5 md5;
	int i;
	int cont=1;
	int zeta=100;
	for (i=0;i<sizeof(dllEntryTab)/sizeof(struct dllEntry);i++)
	{
		char buf[128];
		char *fileBuffer = (char *)malloc(1000000);

		sprintf(buf,"%s",dllEntryTab[i].dllName);
		FILE *f=fopen(buf,"rb");
		int len=0;
		if (f)
		{
			len=fread(fileBuffer,1,1000000,f);
			fclose(f);
		} else {
			cont=0;
		}
		
		if (len>0)
		{			
			if (strcmpi(md5.getMD5Digest(fileBuffer,len),dllEntryTab[i].md5result))
			{
				// Some md5 checksum is incorrect. TA will not continue.
				cont=0;
				zeta-=100;
				break;
			}
		}

		free(fileBuffer);		
	}
	//if (!cont) ExitProcess(0);
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTibiaauto_utilApp object

CTibiaauto_utilApp theApp;
CRITICAL_SECTION ItemsInitCriticalSection;

	



BOOL CTibiaauto_utilApp::InitInstance()
{
	InitializeCriticalSection(&ItemsInitCriticalSection);
	return CWinApp::InitInstance();

}

 CTibiaauto_utilApp::ExitInstance()
{	

	return CWinApp::ExitInstance();

}



void setProcessId(int processId)
{
	CMemUtil::setGlobalProcessId(processId);
}

int getProcessId()
{
	return CMemUtil::getGlobalProcessId();
}


 
void setPipeHandle(HANDLE hPipePar)
{	
	hPipe=hPipePar;
}

CTibiaContainer *memReadContainer(int containerNr)
{
	startMemReader();
	return reader->readContainer(containerNr);
};

void packSenderMoveObjectBetweenContainers(int objectId,int  sourceContNr,int  sourcePos, int targetContNr, int targetPos,int  qty)
{	
	CPackSender sender;
	sender.moveObjectBetweenContainers(objectId, sourceContNr, sourcePos, targetContNr, targetPos, qty);
}

void memReadWriteSelfLightPower(int value)
{
	startMemReader();
	reader->writeSelfLightPower(value);
}

void memReadWriteSelfLightColor(int value)
{
	startMemReader();
	reader->writeSelfLightColor(value);
}

int memReadReadSelfLightPower()
{
	startMemReader();
	return reader->readSelfLightPower();
}

int memReadReadSelfLightColor()
{
	startMemReader();
	return reader->readSelfLightColor();
}



void memReadWriteCreatureLightPower(int creatureNr,int value)
{
	startMemReader();
	reader->writeCreatureLightPower(creatureNr,value);
}

void memReadWriteCreatureLightColor(int creatureNr,int value)
{
	startMemReader();
	reader->writeCreatureLightColor(creatureNr,value);
}

int memReadReadCreatureLightPower(int creatureNr)
{
	startMemReader();
	return reader->readCreatureLightPower(creatureNr);
}

int memReadReadCreatureLightColor(int creatureNr)
{
	startMemReader();
	return reader->readCreatureLightColor(creatureNr);
}



void memReadCancelAttackCoords()
{
	startMemReader();
	reader->cancelAttackCoords();
}
void memReadWriteGotoCoords(int x,int y,int z)
{
	startMemReader();
	reader->writeGotoCoords(x,y,z);
}
int memReadGetLoggedCharNr()
{
	startMemReader();
	return reader->getLoggedCharNr();
}
int memReadGetSelfEventFlags()
{
	startMemReader();
	return reader->getSelfEventFlags();
}
void memReadWriteVisibleCreatureName(int chNr,char *name)
{
	startMemReader();
	reader->writeVisibleCreatureName(chNr,name);
}
CTibiaItem * memReadGetTradeItemPartner(int nr)
{
	startMemReader();
	return reader->getTradeItemPartner(nr);
}
CTibiaItem * memReadGetTradeItemSelf(int nr)
{
	startMemReader();
	return reader->getTradeItemSelf(nr);
}
int memReadGetTradeCountPartner()
{
	startMemReader();
	return reader->getTradeCountPartner();
}
int memReadGetTradeCountSelf()
{
	startMemReader();
	return reader->getTradeCountSelf();
}
int memReadGetAttackedCreature()
{
	startMemReader();
	return reader->getAttackedCreature();
}
char * memReadGetLoggedChar(int processId)
{
	startMemReader();
	return reader->GetLoggedChar(processId);
}
int memReadReadBattleListMax()
{
	startMemReader();
	return reader->readBattleListMax();
} 


int memReadReadBattleListMin()
{	
	startMemReader();
	return reader->readBattleListMin();	
}
CTibiaCharacter * memReadReadVisibleCreature(int nr)
{
	startMemReader();
	return reader->readVisibleCreature(nr);
}
CTibiaItem * memReadReadItem(int locationAddress)
{
	startMemReader();
	return reader->readItem(locationAddress);
}
CTibiaCharacter *memReadReadSelfCharacter()
{
	startMemReader();
	return reader->readSelfCharacter();
}
CTibiaCharacter *memReadGetCharacterByTibiaId(int tibiaId)
{
	startMemReader();
	return reader->getCharacterByTibiaId(tibiaId);
}


void packSenderUseWithObjectFromContainerOnFloor(int sourceObjectId,int sourceContNr,int sourcePos,int targetObjectId,int targetX,int targetY,int targetZ, int method, int extraInfo)
{
	CPackSender sender;
	sender.useWithObjectFromContainerOnFloor(sourceObjectId,sourceContNr,sourcePos,targetObjectId,targetX,targetY,targetZ,method,extraInfo);	
}

CMemConstData getMemConstData()
{	
	return CMemConstData();
}

void packSenderMoveObjectFromFloorToContainer(int objectId,int sourceX,int sourceY,int sourceZ,int targetContNr,int targetPos,int quantity)
{
	CPackSender sender;
	sender.moveObjectFromFloorToContainer(objectId,sourceX,sourceY,sourceZ,targetContNr,targetPos,quantity);
}


///

void packSenderMoveObjectFromContainerToFloor(int objectId, int contNr, int pos, int x, int y, int z,int quantity)
{
	CPackSender sender;
	sender.moveObjectFromContainerToFloor(objectId,contNr,pos,x,y,z,quantity);
}
void packSenderCastRuneAgainstCreature(int contNr, int itemPos, int runeObjectId, int creatureId, int method)
{
	CPackSender sender;
	sender.castRuneAgainstCreature(contNr,itemPos,runeObjectId,creatureId,method);
}
void packSenderCastRuneAgainstHuman(int contNr, int itemPos, int runeObjectId, int targetX, int targetY, int targetZ, int method)
{
	CPackSender sender;
	sender.castRuneAgainstHuman(contNr,itemPos,runeObjectId,targetX,targetY,targetZ, method);
}
void packSenderSendTAMessage(char *msg)
{
	CPackSender sender;
	sender.sendTAMessage(msg);
}
void packSenderUseItemOnFloor(int objectId, int x, int y, int z)
{
	CPackSender sender;
	sender.useItemOnFloor(objectId,x,y,z);
}
void packSenderUseItemInContainer(int objectId, int contNr, int pos)
{
	CPackSender sender;
	sender.useItemInContainer(objectId,contNr,pos);
}
void packSenderOpenContainerFromFloor(int objectId,int x,int y,int z,int targetBag)
{
	CPackSender sender;
	sender.openContainerFromFloor(objectId,x,y,z,targetBag);
}
void packSenderOpenContainerFromContainer(int objectId, int contNrFrom, int contPosFrom, int targetBag)
{
	CPackSender sender;
	sender.openContainerFromContainer(objectId,contNrFrom,contPosFrom,targetBag);
}

void packSenderSendAttackedCreatureToAutoAim(int attackedCreature)
{
	CPackSender sender;
	sender.sendAttackedCreatureToAutoAim(attackedCreature);
}

void packSenderSay(char *msg)
{
	CPackSender sender;
	sender.say(msg);
}

void packSenderSayWhisper(char *msg)
{
	CPackSender sender;
	sender.sayWhisper(msg);
}

void packSenderSayYell(char *msg)
{
	CPackSender sender;
	sender.sayYell(msg);
}

void packSenderTell(char *msg, char *playerName)
{
	CPackSender sender;
	sender.tell(msg,playerName);
}

void packSenderSayOnChan(char *msg, int channelId)
{
	CPackSender sender;
	sender.sayOnChan(msg,channelId);
}

void memReadSetMemIntValue(int address,int value)
{
	CMemUtil::SetMemIntValue(address,value);
}

int memReadGetMemIntValue(int address)
{
	return CMemUtil::GetMemIntValue(address);
}

void memReadSetMemRange(DWORD memAddressStart,DWORD memAddressEnd, char *data)
{
	CMemUtil::SetMemRange(memAddressStart,memAddressEnd,data);
}

void memReadGetMemRange(DWORD memAddressStart,DWORD memAddressEnd, char *data)
{
	CMemUtil::SetMemRange(memAddressStart,memAddressEnd,data);
}

void tibiaMapRemovePointAvailable(int x,int y,int z)
{
	tibiaMap.removePointAvailable(x,y,z);
}
void tibiaMapProhPointClear()
{
	tibiaMap.prohPointClear();
}
void tibiaMapProhPointAdd(int x, int y, int z)
{
	tibiaMap.prohPointAdd(x,y,z);
}
int tibiaMapGetPointUpDown(int x,int y,int z)
{
	return tibiaMap.getPointUpDown(x,y,z);
}
void tibiaMapSetPointUpDown(int x,int y,int z,int updown)
{
	tibiaMap.setPointUpDown(x,y,z,updown);
}
int tibiaMapGetPrevPointZ(int x,int y, int z)
{
	return tibiaMap.getPrevPointZ(x,y,z);
}
int tibiaMapGetPrevPointY(int x,int y, int z)
{
	return tibiaMap.getPrevPointY(x,y,z);
}
int tibiaMapGetPrevPointX(int x,int y, int z)
{
	return tibiaMap.getPrevPointX(x,y,z);
}
void tibiaMapClearPrevPoint()
{
	tibiaMap.clearPrevPoint();
}
void tibiaMapSetPrevPoint(int x,int y,int z,int prevX, int prevY, int prevZ)
{
	tibiaMap.setPrevPoint(x,y,z,prevX,prevY,prevZ);
}
struct point tibiaMapGetRandomPoint()
{
	return tibiaMap.getRandomPoint();
}
void tibiaMapClear()
{
	tibiaMap.clear();
}
void tibiaMapSetPointAsAvailable(int x,int y,int z)
{
	tibiaMap.setPointAsAvailable(x,y,z);
}
int tibiaMapIsPointAvailable(int x,int y,int z)
{
	return tibiaMap.isPointAvailable(x,y,z);
}

int tibiaMapIsPointAvailableNoProh(int x,int y,int z)
{
	return tibiaMap.isPointAvailableNoProh(x,y,z);
}

int tibiaMapSize()
{
	return tibiaMap.size();
}

struct point tibiaMapGetPointByNr(int nr)
{
	return tibiaMap.getPointByNr(nr);
}

char * tibiaItemGetName(int objectId)
{
	return CTibiaItem::getName(objectId);
}

int tibiaItemGetObjectId(char *name)
{
	return CTibiaItem::getObjectId(name);
}

void tibiaItemRefreshItemLists()
{	
	CTibiaItem::itemListsFresh=0;
	CTibiaItem::refreshItemLists();
}

int tibiaItemGetCorpseIdByCreatureName(char *name)
{
	return CTibiaItem::getCorpseIdByCreatureName(name);
}

CUIntArray * tibiaItemGetItemsFoodArray()
{
	return CTibiaItem::getItemsFood();
}


char *tibiaItemGetItemsItems(int nr)
{
	return CTibiaItem::itemsItems[nr];
}
int tibiaItemGetItemsItemsId(int nr)
{
	return CTibiaItem::itemsItemsId[nr];
}
int tibiaItemGetItemsItemsCount()
{
	return CTibiaItem::itemsItemsCount;
}
char *tibiaItemGetItemsFood(int nr)
{
	return CTibiaItem::itemsFood[nr];
}
int tibiaItemGetItemsFoodId(int nr)
{
	return CTibiaItem::itemsFoodId[nr];
}
int tibiaItemGetItemsFoodCount()
{
	return CTibiaItem::itemsFoodCount;
}
char *tibiaItemGetItemsCorpses(int nr)
{
	return CTibiaItem::itemsCorpses[nr];
}
int tibiaItemGetItemsCorpsesId(int nr)
{
	return CTibiaItem::itemsCorpsesId[nr];
}
int tibiaItemGetItemsCorpsesCount()
{
	return CTibiaItem::itemsCorpsesCount;
}
char *tibiaItemGetItemsLooted(int nr)
{
	return CTibiaItem::itemsLooted[nr];
}
int tibiaItemGetItemsLootedId(int nr)
{
	return CTibiaItem::itemsLootedId[nr];
}
int tibiaItemGetItemsLootedCount()
{
	return CTibiaItem::itemsLootedCount;
}

int tibiaItemGetValueForConst(char *code)
{
	return CTibiaItem::getValueForConst(code);
}

void packSenderLogout()
{
	CPackSender sender;
	sender.logout();
}

void packSenderStepMulti(int *direction,int size)
{
	CPackSender sender;
	sender.stepMulti(direction,size);
}

void packSenderCloseContainer(int contNr)
{
	CPackSender sender;
	sender.closeContainer(contNr);
}

void packSenderAttackMode(int mode,int follow)
{
	CPackSender sender;
	sender.attackMode(mode,follow);
}

void packSenderAttack(int tibiaCharId)
{
	CPackSender sender;
	sender.attack(tibiaCharId);
}

int memReadMapGetPointItemsCount(point p)
{
	startMemReader();
	return reader->mapGetPointItemsCount(p);
}
int memReadMapGetPointItemId(point p, int stackNr)
{
	startMemReader();
	return reader->mapGetPointItemId(p,stackNr);
}

int memReadMapGetPointItemExtraInfo(point p, int stackNr,int extraPos)
{
	startMemReader();
	return reader->mapGetPointItemExtraInfo(p,stackNr,extraPos);
}

void memReadMapSetPointItemsCount(point p, int count)
{
	startMemReader();
	reader->mapSetPointItemsCount(p,count);
}
void memReadMapSetPointItemId(point p, int stackNr, int tileId)
{
	startMemReader();
	reader->mapSetPointItemId(p,stackNr,tileId);
}

void packSenderTurnLeft()
{
	CPackSender sender;
	sender.turnLeft();
}

void packSenderTurnRight()
{
	CPackSender sender;
	sender.turnRight();
}

void packSenderTurnUp()
{
	CPackSender sender;
	sender.turnUp();
}

void packSenderTurnDown()
{
	CPackSender sender;
	sender.turnDown();
}

void packSenderMoveObjectFromFloorToFloor(int objectId, int srcX, int srcY, int srcZ, int destX, int destY, int destZ,int quantity)
{
	CPackSender sender;
	sender.moveObjectFromFloorToFloor(objectId, srcX, srcY, srcZ, destX, destY, destZ,quantity);
}


long memReadGetCurrentTm()
{
	startMemReader();
	return reader->getCurrentTm();
}


int ipcBackPipeReadFromPipe(struct ipcMessage *mess,int expectedType)
{
	CIPCBackPipe backPipe;
	return backPipe.readFromPipe(mess,expectedType);
}

void ipcBackPipeInitialiseIPC()
{
	CIPCBackPipe backPipe;
	backPipe.InitialiseIPC();
}

void packSenderSendCreatureInfo(char *name, char *info1, char *info2)
{
	CPackSender sender;
	sender.sendCreatureInfo(name,info1,info2);
}

void packSenderLook(int x,int y, int z,int objectId)
{
	CPackSender sender;
	sender.look(x,y,z,objectId);
}

void packSenderIgnoreLook(int end)
{
	CPackSender sender;
	sender.ignoreLook(end);
}

long memReadGetCurrenTm()
{
	startMemReader();
	return reader->getCurrentTm();
}

void packSenderSendAutoAimConfig(int active, int onlyCreatures, int aimPlayersFromBattle)
{
	CPackSender sender;
	sender.sendAutoAimConfig(active,onlyCreatures,aimPlayersFromBattle);
}


void packSenderSendClearCreatureInfo()
{
	CPackSender sender;
	sender.sendClearCreatureInfo();
}

void memReadWriteEnableRevealCName ()
{
	startMemReader();
	reader->writeEnableRevealCName();
}

void memReadWriteDisableRevealCName ()
{
	startMemReader();
	reader->writeDisableRevealCName();
}

int getKernelMainVersion()
{
	return 2;
}

int getKernelPatchVersion()
{
	return 2;
}

CTibiaTile *getTibiaTile(int tileNr)
{
	CTileReader tileReader;
	return tileReader.getTile(tileNr);
}

void memReadSetRemainingTilesToGo(int val)
{
	startMemReader();
	reader->setRemainingTilesToGo(val);
}

void packSenderEnableCName(int enable)
{
	CPackSender sender;
	sender.enableCName(enable);
}

void variableStoreSetVariable(char *name, char *value)
{
	CVariableStore::setVariable(name,value);
}

char *variableStoreGetVariable(char *name)
{
	return CVariableStore::getVariable(name);
}