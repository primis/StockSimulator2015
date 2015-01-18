#include "sim.h"

const char *symbol[] = {
"mmm","joy","cov","pgr","brcm","nem","gci","trip","aon","mas","emr","so","ctsh",
"pxd","ice","win","abt","jpm","cci","pld","bf.b","nwsa","gps","foxa","apa","ma",
"esv","luv","cl","pbi","ibm","wec","abbv","jnpr","csx","pru","chrw","nee",
"grmn","tsn","aiv","mat","etr","swn","cmcsa","pcl","ip","wyn","ace","ksu","cmi",
"peg","ca","nlsn","gd","tyc","aapl","mkc","eog","se","cma","pnc","ipg","wynn",
"acn","k","cvs","psa","cvc","nke","ge","usb","amat","mcd","eqt","stj","csc",
"rl","iff","xel","act","key","dhi","phm","cog","ni","ggp","ua","adm","mhfi",
"efx","swk","cag","ppg","intu","xrx","adbe","gmcr","dhr","pvh","cam","ne","gis",
"unp","aiz","mck","eqr","spls","cop","ppl","isrg","xlnx","adt","kmb","dri",
"qep","cpb","nbl","gm","unh","t","mjn","ess","sbux","cnx","px","ivz","xl","aes",
"kim","dva","pwr","cof","jwn","gpc","ups","adsk","mwv","el","hot","ed","pcp",
"irm","xyl","aet","kmi","de","qcom","cah","nsc","gnw","mlm","adp","mdt","exc",
"stt","stz","pcln","jec","yhoo","afl","klac","dlph","dgx","cfn","ntrs","gild",
"uri","an","mrk","expe","srcl","glw","pfg","jnj","yum","amg","kss","dal","rrc",
"kmx","noc","gs","utx","azo","met","expd","syk","cost","pg","jci","zmh","a",
"krft","dnr","rtn","ccl","nu","gt","uhs","avgo","kors","esrx","sti","bdx","mos",
"fisv","txt","gas","kr","xray","rht","cat","nrg","googl","unm","avb","mchp",
"xom","symc","bbby","msi","flir","hsy","apd","lb","dvn","regn","cbg","nue",
"goog","urbn","avy","mu","ffiv","syy","brk.b","mur","fls","trv","arg","lll",
"do","rf","cbs","nvda","gww","vfc","avp","msft","fb","trow","bby","myl","flr",
"tmo","akam","lh","dtv","rsg","celg","orly","hal","vlo","bhi","mhk","fdo","tgt",
"biib","nbr","fmc","tif","aa","lrcx","dfs","rai","cnp","oxy","hog","var","bll",
"tap","fast","tel","blk","ndaq","fti","twx","alxn","lm","disca","rhi","ctl",
"omc","har","vtr","bac","mdlz","fdx","te","hrb","nov","f","twc","ati","leg",
"disck","rok","cern","oke","hrs","vrsn","bk","mon","fis","thc","ba","navi",
"fosl","tjx","alle","len","dg","col","cf","orcl","hig","vz","bcr","mnst","fitb",
"tdc","bwa","ntap","ben","tmk","agn","lvlt","dltr","rop","schw","oi","has",
"vrtx","bax","mco","fslr","tso","bxp","nflx","fcx","tss","ads","luk","d","rost",
"chk","pcg","hcp","viab","bbt","ms","fe","txn","bsx","nwl","ftr","tsco","all",
"lly","dov","rcl","cvx","pcar","hcn","v","aig","lyb","etfc","sni","csco","pom",
"hsp","wat","altr","lnc","dow","r","cmg","pll","hp","vno","amt","mtb","emn",
"stx","c","pep","hst","antm""mo","lltc","dps","swy","cb","ph","hes","vmc",
"amp","mac","etn","see","ctxs","pki","hcbk","wfc","amzn","lmt","dte","crm","ci",
"pdco","hpq","wmt","abc","m","ebay","sre","clx","prgo","hum","wdc","aee","l",
"dd","sndk","xec","payx","hd","wba","ame","mnk","ecl","shw","cme","petm","hban",
"wu","aep","lo","duk","scg","cinf","pnr","hon","dis","amgn","mro","eix","sial",
"cms","pfe","itw","wy","axp","low","dnb","slb","ctas","pbct","hrl","wm","aph",
"mpc","ew","spg","coh","pm","ir","whr","adi","mmc","emc","sna","cce","pnw",
"intc","wmb","apc","mar","ea","sjm","ko","psx","teg","wfm" 
};

stock::stock()
{
    posX     = rand() % 630;
    vale     = rand() % 30-25;
    vale    *= 10;
    symbolID = rand() % 500;
    posY     = 460;
    name     = new fstring;
    name->setPosition(posX, posY);
}

stock::~stock()
{
    delete name;
}

void stock::redraw()
{
	char tempbuff[16];
    name->setPosition(posX, posY);
	if(vale < 0) {
		sprintf(tempbuff,"%s%d",symbol[symbolID], vale);		
        name->setText(tempbuff,true);
	} else {
		sprintf(tempbuff,"%d", vale);
        name->setText(tempbuff,false);
    }
    name->redraw();
}

bool stock::isHit(int x, int y)
{
    return name->isHit(x,y);
}

int stock::getValue()
{
    return vale;
}
int stock::getY()
{
	return posY;
}
bool stock::rise(int x, int y)
{
	posY--;
	
	if((posY > (y + 32)) && (posY < y)) {
		if((x > posX) && (x < posX + 12)) {
			return false;
		}
	}
	if (posY < 0) {
		return false;
	}
    return true;
}

