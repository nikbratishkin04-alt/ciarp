
/*Çàïîìíè ýòî, ÿ ïðîñòî ïèøó êàê çàìåòêà, ïîòîì íàïîìíè
òî ÷òî íóæíî äîáàâèòü
==========ÔÐÀÊÖÈÈ========
Áàíäû: Ballas, Grove Street, Vagos, Rifa
Ìàôèÿ: Russian Mafia
ÃÎÑ: Ïðàâèòåëüñòâî, LSPD(ïîëèöèÿ), Íàöèîíàëüíàÿ ãâàðäèÿ, LSMC(âðà÷è), LS-NEWS(òåëå-ðàäèî öåíòð), Òàêñîïàðê
==========ÐÀÁÎÒÀ========
Ðàáîòû: Ôåðìà(ïîëå, ñêîò), ñêîòîáîéíÿ(+ïðîèçâîäñòâåííûé öåõ), Øàõòà(+çàâîä), Ðàçâîç÷èê ñûðüÿ äëÿ çàâîäà/ôåðì/ñêîòîáîèíü, Íåôòåçàâîä(ðàçâîçêà òîïëèâà ïî çàïðàâêàì) ìåõàíèê
==========Èíòåðüåðû=======
24íà7, Ìàãàçèí îðóæèÿ, ìàãàçèí îäåæäû(+ àêñåññóàðû), âñå âèäû çàêóñî÷íûõ ðåñòîðàíîâ áàðîâ è êëóáîâ, êàçèíî, àâòîñàëîí, àâòîøêîëà, ñàëîí ëåòíîãî è âîäíîãî òðàíñïîðòà,
ìåáåëüíûé ìàãàçèí
==========Íîâûå ñèñòåìû=======
Âñå âèäû ëèöåíçèé, ñèñòåìà äîìîâ è ïîêóïêà òðàíñïîðòà, íîâûå êîìàíäû äëÿ ðï, ñèñòåìà ÃÏÑ, äåôîëòíûå êîìàíäû êàê /mm è òï, ñèñòåìà ñêèëëîâ êàê íà ðàáîòå òàê è ïåðñîíàæà
*/



#include <a_samp>
#include <a_vehicles>
#include <a_mysql>
#include <streamer>
#include <sscanf2>
#include <dc_cmd>
#include <Pawn.Regex>
#include <a_actor>
#include <samp_bcrypt>
#pragma warning disable 239

#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASS ""
#define MYSQL_BASE "serv"

#define SPD ShowPlayerDialog
#define SCM SendClientMessage
#define DONT_USE_SCM
//============[COLORS]============
#define COLOR_RED 0xAA3333AA
#define COLOR_WHITE 0xFFFFFFAA
#define COLOR_GREY 0xF696969A
#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_GREEN 0x9EC73DAA
#define COLOR_SYSTEM COLOR_RED
#define COLOR_PINK 0xFFC0CBAA
#define COLOR_BLUE 0x0000BBAA
#define COLOR_LIGHTBLUE 0x33CCFFAA
#define COLOR_ORANGE 0xFF9900AA
#define COLOR_BLACK 0x000000AA
#define TEAM_GROVE_COLOR 0x00D900C8
#define COLOR_GOLD 0xB8860BAA
#define COLOR_PURPLE 0xC2A2DAAA
#define COLOR_CON_GREEN 0x00FF00FF
#define COLOR_DIS_RED 0xFF0000FF
#define COLOR_LIGHTRED 0xFF6347AA
#define COLOR_LIGHTGREEN 0x9ACD32AA
#define COLOR_YELLOW2 0xF5DEB3AA
#define COLOR_FADE1 0xE6E6E6E6
#define COLOR_FADE2 0xC8C8C8C8
#define COLOR_FADE3 0xAAAAAAAA
#define COLOR_FADE4 0x8C8C8C8C
#define COLOR_FADE5 0x6E6E6E6E
#define COLOR_DBLUE 0x2641FEAA
#define COLOR_ALLDEPT 0xFF8282AA
#define COLOR_NEWS 0xFFA500AA
#define COLOR_OOC 0xE0FFFFAA
#define OBJECTIVE_COLOR 0x64000064
#define TEAM_GREEN_COLOR 0xFFFFFFAA
#define TEAM_JOB_COLOR 0xFFB6C1AA
#define TEAM_HIT_COLOR 0xFFFFFF00
#define TEAM_BLUE_COLOR 0x8D8DFF00
#define COLOR_ADD 0x63FF60AA
#define TEAM_VAGOS_COLOR 0xFFC801C8
#define TEAM_BALLAS_COLOR 0xD900D3C8
#define TEAM_AZTECAS_COLOR 0x01FCFFC8
#define TEAM_CYAN_COLOR 0xFF8282AA
#define TEAM_ORANGE_COLOR 0xFF830000
#define TEAM_COR_COLOR 0x39393900
#define TEAM_BAR_COLOR 0x00D90000
#define TEAM_TAT_COLOR 0xBDCB9200
#define TEAM_CUN_COLOR 0xD900D300
#define TEAM_STR_COLOR 0x01FCFF00
#define TEAM_ADMIN_COLOR 0x00808000
#define COLOR_INVIS 0xAFAFAF00
#define COLOR_SPEC 0xBFC0C200

//================================
new MySQL: dbHandle;
new query[256];
new player_skin_index[MAX_PLAYERS];
new PlayerText:btn_left[MAX_PLAYERS];
new PlayerText:btn_right[MAX_PLAYERS];
new PlayerText:btn_select[MAX_PLAYERS];
new male_skins[] = {2, 44, 7, 24, 59, 58};
new female_skins[] = {93, 88, 65, 76, 56, 54};
new bool:in_skin_select[MAX_PLAYERS];
new Float:skin_cam_pos[MAX_PLAYERS][3];
new bool:is_logged[MAX_PLAYERS];
new login_attempts[MAX_PLAYERS];
new Text3D:chat_bubble[MAX_PLAYERS] = {Text3D:INVALID_3DTEXT_ID, ...};
new Float:last_message_time[MAX_PLAYERS];
new message_count[MAX_PLAYERS];
new bool:is_chatting[MAX_PLAYERS];
new money_td_color[MAX_PLAYERS];
new Float:last_me_time[MAX_PLAYERS];
new Float:last_do_time[MAX_PLAYERS];
new Float:last_s_time[MAX_PLAYERS];
new Float:last_n_time[MAX_PLAYERS];
new Float:last_pay_time[MAX_PLAYERS];
new pay_count[MAX_PLAYERS];
new pay_limit_timer[MAX_PLAYERS];
new bool:payday_today[MAX_PLAYERS];
new Text:LOGO_TD[2];
new bool:logo_shown[MAX_PLAYERS];
new gardener_npc;
new Float:weed_markers[20][3];
new bool:weed_collected[MAX_PLAYERS][20];
new weed_count[MAX_PLAYERS];
new bool:working_gardener[MAX_PLAYERS];
new weed_objects[MAX_PLAYERS][20];
new Float:last_pickup_time[MAX_PLAYERS];
new Float:last_pass_time[MAX_PLAYERS];
new passport_npc_actor;
new bool:passport_ready[MAX_PLAYERS];
new bool:passport_waiting[MAX_PLAYERS];
new LastPassportID = 100000;
new PlayerText:money_td[MAX_PLAYERS];
new money_td_timer[MAX_PLAYERS];
new money_td_alpha[MAX_PLAYERS];
new Float:active_time[MAX_PLAYERS];
new afk_seconds[MAX_PLAYERS];
new bool:is_afk[MAX_PLAYERS];
new instructor_npc;
new exam_errors[MAX_PLAYERS];
new bool:exam_theory_passed[MAX_PLAYERS];
new exam_cars[3];
new bool:exam_practice_started[MAX_PLAYERS];
new bool:exam_practice_passed[MAX_PLAYERS];
new last_money[MAX_PLAYERS];
new PlayerText:hunger_bg[MAX_PLAYERS];
new PlayerText:thirst_bg[MAX_PLAYERS];
new Float:exam_checkpoints[][3] = {
    {1314.8700, -1839.3376, 13.3828},
    {1314.8669, -1800.8217, 13.3828},
    {1314.8622, -1734.5879, 13.3828},
    {1386.1489, -1734.7797, 13.3906},
    {1472.6533, -1735.0104, 13.3828},
    {1561.6580, -1735.2456, 13.3828},
    {1567.6992, -1786.2306, 13.3828},
    {1566.7100, -1867.1765, 13.3828},
    {1500.5127, -1869.8241, 13.3828},
    {1441.7512, -1869.9065, 13.3906},
    {1351.9020, -1859.5635, 13.3828},
    {1289.0024, -1858.9503, 13.5469}
};
new exam_checkpoint_index[MAX_PLAYERS];
new exam_practice_time[MAX_PLAYERS];
new exam_practice_timer[MAX_PLAYERS];
forward ExamPracticeTimer(playerid);
new bool:has_driver_license[MAX_PLAYERS];
new bool:vehicle_engine[MAX_VEHICLES];

// ========== ÊÀÇÈÍÎ: ÑÈÑÒÅÌÀ ÐÓËÅÒÊÈ ===================================================
new bool:at_roulette[MAX_PLAYERS];
new PlayerText:roulette_exit_td[MAX_PLAYERS];
new bool:roulette_creating[MAX_PLAYERS];
new Float:roulette_cam_save[MAX_PLAYERS][6];
new roulette_chip_object[MAX_PLAYERS];
new roulette_chip_position[MAX_PLAYERS];
new bool:roulette_chip_created[MAX_PLAYERS];
new roulette_wheel_object;
new roulette_spin_timer;
new Float:roulette_spin_angle;
new roulette_spin_count;
new Text3D:roulette_timer_3d;
new Text:roulette_number_td;
new roulette_number_timer;
new roulette_number_index;
new roulette_display_number;
new roulette_display_timer;
new Float:roulette_display_alpha;
new roulette_wheel_numbers[] = {
    0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13, 36, 11, 30, 8, 23, 10, 5, 24, 16, 33, 1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26
};

new Float:roulette_chip_positions[49][3] = {
    {1946.1080, 1007.9578, 992.3395},
    {1946.24854, 1007.74939, 992.3395},
    {1946.24854, 1007.99237, 992.3395},
    {1946.24854, 1008.23407, 992.3395},
    {1946.39673, 1007.74939, 992.3395},
    {1946.39673, 1007.99237, 992.3395},
    {1946.39673, 1008.23407, 992.3395},
    {1946.55359, 1007.74384, 992.3395},
    {1946.54553, 1007.98688, 992.3395},
    {1946.54810, 1008.22864, 992.3395},
    {1946.69885, 1007.74384, 992.3395},
    {1946.68848, 1007.98700, 992.3395},
    {1946.69080, 1008.22870, 992.3395},
    {1946.83600, 1007.74384, 992.3395},
    {1946.83600, 1007.98688, 992.3395},
    {1946.83600, 1008.22864, 992.3395},
    {1946.9620, 1007.74384, 992.3395},
    {1946.9620, 1007.98700, 992.3395},
    {1946.9620, 1008.22870, 992.3395},
    {1947.1090, 1007.74384, 992.3395},
    {1947.1090, 1007.98688, 992.3395},
    {1947.1090, 1008.22864, 992.3395},
    {1947.2600, 1007.74384, 992.3395},
    {1947.2600, 1007.98700, 992.3395},
    {1947.2600, 1008.22870, 992.3395},
    {1947.3860, 1007.74384, 992.3395},
    {1947.3860, 1007.98688, 992.3395},
    {1947.3860, 1008.22864, 992.3395},
    {1947.5300, 1007.74384, 992.3395},
    {1947.5300, 1007.98700, 992.3395},
    {1947.5300, 1008.22870, 992.3395},
    {1947.6780, 1007.74384, 992.3395},
    {1947.6780, 1007.98688, 992.3395},
    {1947.6780, 1008.22864, 992.3395},
    {1947.8190, 1007.74384, 992.3395},
    {1947.8190, 1007.98700, 992.3395},
    {1947.8190, 1008.22870, 992.3395},
    {1947.9575, 1007.74384, 992.3395},
    {1947.9575, 1007.98700, 992.3395},
    {1947.9575, 1008.22870, 992.3395},
    {1946.47839, 1007.49915, 992.3395},
    {1947.09827, 1007.51056, 992.3395},
    {1947.70715, 1007.50348, 992.3395},
    {1946.31848, 1007.26764, 992.3395},
    {1946.61084, 1007.26898, 992.3395},
    {1946.92578, 1007.26532, 992.3395},
    {1947.21973, 1007.26190, 992.3395},
    {1947.4750, 1007.3118, 992.3395},
    {1947.7330, 1007.3118, 992.3395}
};
new roulette_bet_amount[MAX_PLAYERS];
new roulette_bet_position[MAX_PLAYERS];
new bool:roulette_bet_placed[MAX_PLAYERS];

new roulette_spinning = 0;
new roulette_winner_number = -1;
new roulette_timer;
new bool:roulette_round_started = false;
new roulette_countdown = 15;
new bool:croupier_played;
new roulette_chip_public[MAX_PLAYERS];
new PlayerText:casinoo_PTD[MAX_PLAYERS][6];
new Text:roulette_mouse_capture;

new roul_npc;

new bike_npc;
new bool:bike_rented[MAX_PLAYERS];
new rented_bike_id[MAX_PLAYERS];
new bike_empty_time[MAX_PLAYERS];
new bike_rental_timer;

new hotdog_npc;

new hunger_damage_timer;
new PlayerText:hunger_td[MAX_PLAYERS];
new PlayerText:thirst_td[MAX_PLAYERS];
new hunger_timer;

//========================================================================================================
enum
{
	DLG_NONE,
	DLG_REG,
	DLG_REG_GENDER,
	DLG_REG_SKIN,
	DLG_LOGIN
}
enum PLAYER_INFO
{
	id,
	name[MAX_PLAYER_NAME + 1],
	pass[61],
	gender,
	skin,
	admin_level,
	money,
	pLevel,
	pExp,
	pPassportID,
	pDriverLicense,
	pHunger,
	pThirst,
	Float:pHealth,
};
new player_info[MAX_PLAYERS][PLAYER_INFO];

main()
{
	print("========Mode v.1========");
}
public OnGameModeInit()
{
	dbHandle = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_BASE);
	if(mysql_errno() != 0)
	{
		print("[MYSQL íå ïîäêëþ÷åíà ê ÁÄ]");
		return SendRconCommand("exit");
	}
	else
	{
	    print("Óñïåøíîå ïîäêëþ÷åíèå ê ÁÄ");
	}
	mysql_tquery(dbHandle, "SELECT MAX(passport_id) FROM accounts", "LoadLastPassportID", "");
	DisableInteriorEnterExits();
	EnableStuntBonusForAll(0);
	SetTimer("CheckActiveTime", 10000, true);
    // Ëîãîòèï ñåðâåðà
	LOGO_TD[0] = TextDrawCreate(549.0002, 8.7259, "California");
	TextDrawLetterSize(LOGO_TD[0], 0.4000, 1.6000);
	TextDrawAlignment(LOGO_TD[0], 1);
	TextDrawColor(LOGO_TD[0], -5963521);
	TextDrawSetOutline(LOGO_TD[0], 1);
	TextDrawBackgroundColor(LOGO_TD[0], 255);
	TextDrawFont(LOGO_TD[0], 3);
	TextDrawSetProportional(LOGO_TD[0], 1);
	TextDrawSetShadow(LOGO_TD[0], 0);

	LOGO_TD[1] = TextDrawCreate(575.6666, 16.6074, "RolePlay");
	TextDrawLetterSize(LOGO_TD[1], 0.4000, 1.6000);
	TextDrawTextSize(LOGO_TD[1], 28.0000, 0.0000);
	TextDrawAlignment(LOGO_TD[1], 1);
	TextDrawColor(LOGO_TD[1], -1);
	TextDrawSetOutline(LOGO_TD[1], 1);
	TextDrawBackgroundColor(LOGO_TD[1], 255);
	TextDrawFont(LOGO_TD[1], 1);
	TextDrawSetProportional(LOGO_TD[1], 1);
	TextDrawSetShadow(LOGO_TD[1], 0);
	// ========== ÌÀÏÏÈÍÃ ÑÀÄÎÂÍÈÊÀ ==========
	CreateObject(1431, 1958.04089, -1170.06543, 19.85520, 4.00000, 4.00000, -105.00000);
	CreateObject(678, 1958.43396, -1171.31140, 19.17630, 0.00000, 0.00000, -18.97340);
	CreateObject(16337, 1957.15308, -1167.57739, 19.44710, 0.00000, 0.00000, 89.01540);
	CreateObject(1227, 1957.59863, -1165.52197, 20.39330, 0.00000, 0.00000, 177.99580);
	CreateObject(1458, 1957.14246, -1172.22729, 19.44560, 0.00000, 0.00000, 50.00000);
	CreateObject(337, 1955.66626, -1169.90771, 19.94350, 0.00000, 200.00000, 100.00000);
	// NPC Ñàäîâíèê
	gardener_npc = CreateActor(94, 1955.8096, -1169.4681, 20.3881, 100.4234);
	SetActorVirtualWorld(gardener_npc, 1);
	ApplyActorAnimation(gardener_npc, "PED", "IDLE_STANCE", 4.1, 1, 0, 0, 0, 0);
	Create3DTextLabel("{FF9900}Ñàäîâíèê\n{33AA33}/talk {FFFFFF}- ÷òîáû ïîãîâîðèòü.", 0xFFFFFFFF,
    1955.8096, -1169.4681, 20.7881, 10.0, 1, 0);
	// Ìàðêåðû ñîðíÿêîâ
	weed_markers[0][0] = 1948.1300; weed_markers[0][1] = -1177.5226; weed_markers[0][2] = 20.0688;
	weed_markers[1][0] = 1938.9357; weed_markers[1][1] = -1179.2034; weed_markers[1][2] = 20.2122;
	weed_markers[2][0] = 1930.4904; weed_markers[2][1] = -1173.1111; weed_markers[2][2] = 21.2646;
	weed_markers[3][0] = 1922.7690; weed_markers[3][1] = -1173.1018; weed_markers[3][2] = 22.2455;
	weed_markers[4][0] = 1920.9719; weed_markers[4][1] = -1180.1086; weed_markers[4][2] = 21.8003;
	weed_markers[5][0] = 1926.0649; weed_markers[5][1] = -1184.4446; weed_markers[5][2] = 20.8661;
	weed_markers[6][0] = 1925.4244; weed_markers[6][1] = -1191.2185; weed_markers[6][2] = 20.3641;
	weed_markers[7][0] = 1921.6515; weed_markers[7][1] = -1200.4877; weed_markers[7][2] = 20.0432;
	weed_markers[8][0] = 1922.3832; weed_markers[8][1] = -1208.3424; weed_markers[8][2] = 19.9277;
	weed_markers[9][0] = 1916.5316; weed_markers[9][1] = -1213.1332; weed_markers[9][2] = 19.5169;
	weed_markers[10][0] = 1908.7585; weed_markers[10][1] = -1206.3209; weed_markers[10][2] = 19.8998;
	weed_markers[11][0] = 1900.6938; weed_markers[11][1] = -1207.1750; weed_markers[11][2] = 19.5345;
	weed_markers[12][0] = 1892.3926; weed_markers[12][1] = -1200.7286; weed_markers[12][2] = 20.4907;
	weed_markers[13][0] = 1886.1578; weed_markers[13][1] = -1188.0107; weed_markers[13][2] = 22.6230;
	weed_markers[14][0] = 1886.5157; weed_markers[14][1] = -1176.1906; weed_markers[14][2] = 23.9251;
	weed_markers[15][0] = 1876.1771; weed_markers[15][1] = -1183.0294; weed_markers[15][2] = 23.6335;
	weed_markers[16][0] = 1871.6654; weed_markers[16][1] = -1192.1311; weed_markers[16][2] = 22.8452;
	weed_markers[17][0] = 1866.0338; weed_markers[17][1] = -1207.5258; weed_markers[17][2] = 20.7243;
	weed_markers[18][0] = 1867.1569; weed_markers[18][1] = -1224.0840; weed_markers[18][2] = 17.8027;
	weed_markers[19][0] = 1877.1705; weed_markers[19][1] = -1239.9105; weed_markers[19][2] = 14.4550;
	// ========== ÏÀÑÏÎÐÒÍÛÉ ÑÒÎË ==========
	CreateDynamicObject(19377, 2443.30005, -1592.19995, 3008.0, 0.00, 270, 0.00, 2);
	CreateDynamicObject(19461, 2443.69995, -1596.90002, 3009.80005, 0.00, 0.00, 270, 2);
	CreateDynamicObject(19461, 2443.69995, -1587.5, 3009.80005, 0.00, 0.00, 270, 2);
	CreateDynamicObject(19461, 2448.3999, -1592.19995, 3009.80005, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(19461, 2440.18408, -1592.40295, 3009.80005, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(19377, 2443.30005, -1592.19995, 3011.6001, 0.00, 90, 0.00, 2);
	CreateDynamicObject(19446, 2440.57788, -1589.39795, 3007.19995, 0.00, 0.00, 270, 2);
	CreateDynamicObject(19384, 2447.0, -1589.40002, 3009.80005, 0.00, 0.00, 270, 2);
	CreateDynamicObject(19446, 2440.57788, -1589.39905, 3012.0, 0.00, 0.00, 270, 2);
	CreateDynamicObject(19802, 2446.25195, -1589.44702, 3008.07788, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(2165, 2441.74512, -1588.81897, 3008.08594, 0.00, 0.00, 179.52, 2);
	CreateDynamicObject(2164, 2442.771, -1587.58997, 3008.09204, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(2167, 2444.54199, -1587.58606, 3008.09399, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(2197, 2441.89697, -1588.31897, 3008.06104, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(1806, 2440.65601, -1587.94702, 3008.07593, 0.00, 0.00, 200, 2);
	CreateDynamicObject(19859, 2445.31104, -1587.58606, 3009.34106, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(19859, 2440.57104, -1596.802, 3009.34106, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(2611, 2448.2771, -1588.41797, 3009.55005, 0.00, 0.00, 270, 2);
	CreateDynamicObject(2611, 2448.27588, -1595.81897, 3009.55005, 0.00, 0.00, 270, 2);
	CreateDynamicObject(1330, 2447.83203, -1587.94897, 3008.56201, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(2310, 2447.97705, -1591.52405, 3008.58496, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(2310, 2447.93408, -1592.27197, 3008.58496, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(2310, 2447.91211, -1593.02002, 3008.58496, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(2310, 2447.88696, -1593.76794, 3008.58496, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(2310, 2447.88501, -1594.51599, 3008.58496, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(2175, 2447.83398, -1596.33899, 3008.08789, 0.00, 0.00, 179.92, 2);
	CreateDynamicObject(11705, 2447.15308, -1596.40295, 3008.8689, 0.00, 0.00, 145.96, 2);
	CreateDynamicObject(2894, 2447.86792, -1596.37, 3008.87891, 0.00, 0.00, 14.03, 2);
	CreateDynamicObject(1649, 2444.36499, -1589.39795, 3009.75195, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(1649, 2445.46899, -1594.32397, 3009.75195, 0.00, 0.00, 270, 2);
	CreateDynamicObject(1649, 2445.46875, -1594.32324, 3009.75195, 0.00, 0.00, 89.95, 2);
	CreateDynamicObject(19428, 2445.46289, -1591.823, 3009.83594, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(19428, 2445.42505, -1596.01794, 3009.83594, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(2961, 2444.69702, -1596.81396, 3009.479, 0.00, 0.00, 0.00, 2);
	CreateDynamicObject(1620, 2444.78711, -1596.81396, 3010.86401, 0.00, 0.00, 269.9, 2);
	CreateDynamicObject(366, 2444.90698, -1596.75403, 3008.68604, 355.44, 40.68, 11.82, 2);
	CreateDynamicObject(3785, 2442.68896, -1593.81006, 3011.42407, 0.00, 90, 90.0, 2);
	CreateDynamicObject(3785, 2446.95093, -1594.35205, 3011.42407, 0.00, 90, 90.0, 2);
	passport_npc_actor = CreateActor(76, 2441.2012, -1588.1819, 3009.0859, 184.4641);
	SetActorVirtualWorld(passport_npc_actor, 2);
	Create3DTextLabel("{FF9900}Ïàñïîðòèñòêà\n{33AA33}/talk {FFFFFF}- ÷òîáû ïîãîâîðèòü", 0xFFFFFFFF,
    2441.2012, -1588.1819, 3009.4859, 10.0, 2, 0);
	CreateDynamicObject(16400, 1541.13403, -1808.35498, 12.423, 0.00, 0.00, 179.48, 1);
	CreatePickup(1318, 1, 1545.6157, -1811.4038, 14.4699, 1);
	CreatePickup(1318, 1, 2441.2732, -1596.4253, 3009.0859, 2);
	CreateDynamicObject(9247, 1299.11902, -1874.77295, 19.356, 0.00, 0.00, 90, 1);
	CreateDynamicObject(970, 1302.86694, -1862.255, 13.098, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(2933, 1289.75903, -1869.38696, 14.262, 0.00, 0.00, 180, 1);
	// ========== ÈÍÒÅÐÜÅÐ Â ÌÈÐÅ 3 ==========
	CreateDynamicObject(19378, 1192.01099, -1808.22095, 3000.0, 0.00, 90, 0.00, 3);
	CreateDynamicObject(19450, 1197.172, -1808.22205, 3001.83911, 0.00, 0.00, 0.00, 3);
	CreateDynamicObject(19450, 1187.68201, -1808.21997, 3001.83594, 0.00, 0.00, 0.00, 3);
	CreateDynamicObject(19450, 1192.41895, -1812.94104, 3001.83594, 0.00, 0.00, 270, 3);
	CreateDynamicObject(19450, 1192.40906, -1803.49304, 3001.83594, 0.00, 0.00, 270, 3);
	CreateDynamicObject(19377, 1192.01001, -1808.22803, 3003.6731, 0.00, 90, 0.00, 3);
	CreateDynamicObject(19859, 1188.698, -1803.57898, 3001.34106, 0.00, 0.00, 0.00, 3);
	CreateDynamicObject(19431, 1188.56995, -1808.42603, 3001.83594, 0.00, 0.00, 90, 3);
	CreateDynamicObject(1649, 1190.88696, -1808.38501, 3001.76489, 0.00, 270, 180, 3);
	CreateDynamicObject(1649, 1190.88696, -1808.38501, 3001.91602, 0.00, 90, 0.00, 3);
	CreateDynamicObject(19388, 1194.06995, -1808.44397, 3001.83594, 0.00, 0.00, 90, 3);
	CreateDynamicObject(19431, 1196.45105, -1808.44299, 3001.83203, 0.00, 0.00, 90, 3);
	CreateDynamicObject(1502, 1194.75195, -1808.50806, 3000.0769, 0.00, 0.00, 40, 3);
	CreateDynamicObject(2009, 1195.54395, -1805.11206, 3000.0, 0.00, 0.00, 0.00, 3);
	CreateDynamicObject(2161, 1197.08704, -1806.63196, 3000.08594, 0.00, 0.00, 270, 3);
	CreateDynamicObject(1806, 1196.84302, -1804.69702, 3000.08594, 0.00, 0.00, 42, 3);
	CreateDynamicObject(366, 1196.89697, -1808.375, 3000.68311, 0.00, 40.73, 60, 3);
	CreateDynamicObject(2894, 1195.51904, -1804.59705, 3000.80493, 0.00, 0.00, 246, 3);
	CreateDynamicObject(19807, 1195.90405, -1804.15601, 3000.88794, 0.00, 0.00, 16, 3);
	CreateDynamicObject(1546, 1195.57104, -1805.51404, 3000.89404, 0.00, 0.00, 0.00, 3);
	CreateDynamicObject(2961, 1192.12, -1803.57898, 3001.65503, 0.00, 0.00, 356, 3);
	CreateDynamicObject(1620, 1197.08606, -1807.45898, 3002.81104, 0.00, 0.00, 0.00, 3);
	CreateDynamicObject(1999, 1195.63599, -1812.32703, 3000.08594, 0.00, 0.00, 90, 3);
	CreateDynamicObject(1999, 1193.55603, -1812.34595, 3000.08594, 0.00, 0.00, 90, 3);
	CreateDynamicObject(1999, 1191.58606, -1812.34705, 3000.08594, 0.00, 0.00, 90, 3);
	CreateDynamicObject(1999, 1189.16003, -1812.328, 3000.08594, 0.00, 0.00, 90, 3);
	CreateDynamicObject(1811, 1196.62, -1811.54395, 3000.69604, 0.00, 0.00, 0.00, 3);
	CreateDynamicObject(1811, 1194.37195, -1811.66199, 3000.69604, 0.00, 0.00, 0.00, 3);
	CreateDynamicObject(1811, 1192.36401, -1811.54395, 3000.69604, 0.00, 0.00, 0.00, 3);
	CreateDynamicObject(1811, 1189.89795, -1811.53101, 3000.69604, 0.00, 0.00, 0.00, 3);

	CreatePickup(1318, 1, 1302.3058, -1868.9077, 13.5469, 1);
	CreatePickup(1318, 1, 1189.4663, -1803.9528, 3001.0859, 3);
	instructor_npc = CreateActor(59, 1196.3639, -1804.8857, 3001.0859, 89.1009);
	SetActorVirtualWorld(instructor_npc, 3);
	ApplyActorAnimation(instructor_npc, "PED", "IDLE_STANCE", 4.1, 1, 0, 0, 0, 0);
	Create3DTextLabel("{FF9900}Èíñòðóêòîð\n{33AA33}/talk {FFFFFF}- ÷òîáû ïîãîâîðèòü", 0xFFFFFFFF,
 	1196.3639, -1804.8857, 3001.4859, 10.0, 3, 0);
 	exam_cars[0] = CreateVehicle(445, 1297.8899, -1866.3218, 13.5469, 0.0, 1, 1, 0);
	exam_cars[1] = CreateVehicle(445, 1294.8899, -1866.3218, 13.5469, 0.0, 1, 1, 0);
	exam_cars[2] = CreateVehicle(445, 1291.8899, -1866.3218, 13.5469, 0.0, 1, 1, 0);
	for(new i = 0; i < 3; i++)
	{
	    SetVehicleVirtualWorld(exam_cars[i], 1);
	    ChangeVehicleColor(exam_cars[i], 1, 1);
	    SetVehicleNumberPlate(exam_cars[i], "EXAM");
	    SetVehicleParamsEx(exam_cars[i], 0, 0, 0, 0, 0, 0, 0);
	    SetVehicleHealth(exam_cars[i], 1000.0);
	    vehicle_engine[exam_cars[i]] = false;
	}
	//==================ÑÏÀÂÍ=================================================================================
	CreateDynamicObject(970, 1756.63184, -1632.77246, 13.951, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(970, 1754.57898, -1634.83301, 13.945, 0.00, 0.00, 270.02, 1);
	CreateDynamicObject(970, 1754.58398, -1638.95105, 13.945, 0.00, 0.00, 270.016, 1);
	CreateDynamicObject(970, 1754.58606, -1643.06799, 13.945, 0.00, 0.00, 270.016, 1);
	CreateDynamicObject(970, 1756.21997, -1646.40796, 13.945, 0.00, 0.00, 322.016, 1);
	CreateDynamicObject(970, 1768.48804, -1682.25598, 13.967, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(970, 1772.61401, -1682.255, 13.967, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(970, 1776.75195, -1682.25305, 13.967, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(970, 1780.86499, -1682.25696, 13.967, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(970, 1784.98901, -1682.26099, 13.967, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(970, 1789.09998, -1682.26501, 13.967, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(970, 1793.20801, -1682.26099, 13.967, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(970, 1795.27405, -1680.198, 13.967, 0.00, 0.00, 90, 1);
	CreateDynamicObject(1215, 1766.95703, -1680.71997, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1766.94202, -1679.21997, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1766.96106, -1677.71997, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1766.97803, -1676.21997, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1766.99402, -1674.71997, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1767.01001, -1673.21997, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1767.02698, -1671.71997, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1767.04004, -1670.24194, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1767.05701, -1668.71594, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1767.07397, -1667.23706, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1767.08997, -1665.73596, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1767.10706, -1664.23499, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1767.04102, -1662.73206, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1767.05798, -1661.23206, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1767.07202, -1659.74402, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1767.08801, -1658.24304, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1767.10498, -1656.74194, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1766.11304, -1655.95703, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1764.61206, -1655.93994, 13.971, 0.00, 0.00, 0.00);
	CreateDynamicObject(1215, 1763.11096, -1655.92297, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1761.58899, -1655.90906, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1761.58887, -1655.9082, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1760.08997, -1655.875, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1758.54297, -1655.88599, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1757.83899, -1655.23999, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1757.91394, -1653.74194, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1757.98901, -1652.24304, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1758.06396, -1650.74402, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1758.03198, -1649.23596, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1215, 1758.03125, -1649.23535, 13.971, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(14468, 1777.22095, -1672.79602, 14.688, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(14468, 1774.64502, -1674.77795, 14.688, 0.00, 0.00, 62, 1);
	CreateDynamicObject(14468, 1774.58301, -1677.77502, 14.688, 0.00, 0.00, 111.996, 1);
	CreateDynamicObject(14468, 1777.66602, -1679.48706, 14.688, 0.00, 0.00, 175.995, 1);
	CreateDynamicObject(14468, 1780.36401, -1678.21802, 14.688, 0.00, 0.00, 231.99, 1);
	CreateDynamicObject(14468, 1780.61597, -1674.34998, 14.688, 0.00, 0.00, 293.987, 1);
	CreateDynamicObject(869, 1761.87402, -1652.31299, 14.334, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(869, 1761.58704, -1650.99695, 14.334, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1233, 1755.06006, -1663.66003, 14.11, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1340, 1761.896, -1683.62, 13.526, 0.00, 0.00, 90, 1);
	CreateDynamicObject(16003, 1758.43396, -1683.828, 13.92, 0.00, 0.00, 180, 1);
	CreateDynamicObject(1281, 1761.74695, -1679.63696, 13.36, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1281, 1761.72803, -1676.13, 13.36, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(1280, 1772.67505, -1673.49194, 13.822, 0.00, 0.00, 330, 1);
	CreateDynamicObject(1280, 1777.56494, -1670.56995, 13.831, 0.00, 0.00, 270.919, 1);
	CreateDynamicObject(1280, 1772.85498, -1679.30103, 13.824, 0.00, 0.00, 30, 1);
	CreateDynamicObject(1216, 1767.81604, -1681.80896, 14.113, 0.00, 0.00, 179.088, 1);
	CreateDynamicObject(1216, 1770.32605, -1681.86499, 14.113, 0.00, 0.00, 179.088, 1);
	CreateDynamicObject(1216, 1773.005, -1681.86694, 14.113, 0.00, 0.00, 179.088, 1);
	CreateDynamicObject(19184, -1788.54297, -47.948, 13.13, 0.00, 0.00, 0.00, 1);
	CreateDynamicObject(983, 1756.26196, -1679.88306, 13.236, 0.00, 0.00, 16, 1);
	CreateDynamicObject(2754, 1774.06799, -1660.36902, 14.297, 0.00, 0.00, 38, 1);

	CreatePickup(1318, 1, 1022.4791, -1121.4207, 23.8701, 1);
	CreatePickup(1318, 1, 2019.0723, 1017.8080, 996.8750, 10);
    CreateDynamicObject(2098, 1945.08630, 1007.91602, 993.33978, 0.00000, 0.00000, 90.00000, 10);
	CreateDynamicObject(2098, 1945.08618, 1017.93750, 993.33978, 0.00000, 0.00000, 90.00000, 10);
	CreateDynamicObject(2098, 1945.08691, 1027.89783, 993.33978, 0.00000, 0.00000, 90.00000, 10);
	CreateDynamicObject(1978, 1946.68030, 1007.92188, 992.50983, 0.00000, 0.00000, 90.00000, 10);
	roulette_wheel_object = CreateObject(1979, 1945.33325, 1007.72662, 992.51978, 0.0, 0.0, 137.01343);
	CreateDynamicObject(1978, 1946.69263, 1017.96521, 992.50983, 0.00000, 0.00000, 90.00000, 10);
	CreateDynamicObject(1978, 1946.69263, 1027.91260, 992.50983, 0.00000, 0.00000, 90.00000, 10);
	CreateDynamicObject(2785, 1947.91882, 1012.35297, 992.29059, 0.00000, 0.00000, 0.00000, 10);
	CreateDynamicObject(2785, 1947.92334, 1013.27112, 992.29059, 0.00000, 0.00000, 180.00000, 10);
	CreateDynamicObject(2785, 1947.84351, 1023.18890, 992.29059, 0.00000, 0.00000, 180.00000, 10);
	CreateDynamicObject(2785, 1947.84717, 1022.30322, 992.29059, 0.00000, 0.00000, 0.00000, 10);

	roul_npc = CreateActor(171, 1944.4851, 1007.9274, 992.4688, 270.0744);
	SetActorVirtualWorld(roul_npc, 10);
	ApplyActorAnimation(roul_npc, "DEALER", "DEALER_IDLE", 4.1, 1, 0, 0, 0, 0);

	roulette_timer_3d = Create3DTextLabel(" ", 0xFFFFFFFF, 1945.33325, 1007.72662, 992.9, 10.0, 10, 0);
	roulette_timer = -1;
	croupier_played = false;

	Create3DTextLabel("{FF9900}Ðóëåòêà\n{33AA33}/play{FFFFFF} - ×òîáû èãðàòü\n Ñòàâêà îò {33AA33}100$ {FFFFFF}äî {33AA33}1000$", 0xFFFFFFFF,
    1944.4851, 1007.9274, 992.5, 15.0, 10, 0);

    roulette_number_td = TextDrawCreate(320.0, 100.0, "0");
	TextDrawLetterSize(roulette_number_td, 0.80, 3.20);
	TextDrawAlignment(roulette_number_td, 2);
	TextDrawColor(roulette_number_td, 0x00FF00FF);
	TextDrawSetOutline(roulette_number_td, 2);
	TextDrawBackgroundColor(roulette_number_td, 0x000000FF);
	TextDrawFont(roulette_number_td, 2);
	TextDrawSetProportional(roulette_number_td, 1);
	TextDrawSetShadow(roulette_number_td, 0);

	roulette_mouse_capture = TextDrawCreate(0.0, 0.0, "_");
	TextDrawUseBox(roulette_mouse_capture, 1);
	TextDrawBoxColor(roulette_mouse_capture, 0x00000000);
	TextDrawTextSize(roulette_mouse_capture, 640.0, 480.0);
	TextDrawAlignment(roulette_mouse_capture, 1);
	TextDrawFont(roulette_mouse_capture, 1);
	TextDrawSetShadow(roulette_mouse_capture, 0);
	TextDrawSetOutline(roulette_mouse_capture, 0);
	TextDrawSetSelectable(roulette_mouse_capture, 1);

	bike_npc = CreateActor(72, 1757.4216, -1682.4900, 13.4919, 321.4049);
	SetActorVirtualWorld(bike_npc, 1);
	ApplyActorAnimation(bike_npc, "PED", "IDLE_STANCE", 4.1, 1, 0, 0, 0, 0);
	Create3DTextLabel("{FF9900}Ïðîêàò÷èê\n{33AA33}/talk {FFFFFF}- ÷òîáû ïîãîâîðèòü", 0xFFFFFFFF,
    1757.4216, -1682.4900, 13.8919, 10.0, 1, 0);
    bike_rental_timer = SetTimer("CheckEmptyBikes", 60000, true);

    hunger_timer = SetTimer("UpdateHungerAndThirst", 120000, true);
	hunger_damage_timer = SetTimer("HungerDamage", 10000, true);

	hotdog_npc = CreateActor(168, 1761.9163, -1684.6316, 13.3984, 1.3002);
	SetActorVirtualWorld(hotdog_npc, 1);
	ApplyActorAnimation(hotdog_npc, "PED", "IDLE_STANCE", 4.1, 1, 0, 0, 0, 0);
	Create3DTextLabel("{FF9900}Ïðîäàâåö õîò-äîãîâ\n{33AA33}/talk {FFFFFF}- ÷òîáû ïîãîâîðèòü", 0xFFFFFFFF,
    1761.9163, -1684.6316, 13.8919, 10.0, 1, 0);

	SetTimer("SaveHealthTimer", 30000, true); // Ñîõðàíÿåò çäîðîâüå êàæäûå 30 ñåêóíä

	SetTimer("SyncPayDay", 1000, true);

	SetGameModeText("CaliforiaRP");
	ShowPlayerMarkers(0);
	return 1;
}

public OnGameModeExit()
{
    KillTimer(hunger_timer);
    KillTimer(hunger_damage_timer);
    KillTimer(bike_rental_timer);
    mysql_close(dbHandle);
    return 1;
}
public OnPlayerRequestClass(playerid, classid)
{
	if(in_skin_select[playerid]) return 0;
	SetPlayerColor(playerid, 0xFFFFFFFF);
	SetPlayerPos(playerid, 1897.6498,-1151.2196,24.3634);
	SetPlayerCameraPos(playerid, 1907.7559,-1159.6423,23.9278);
	SetPlayerCameraLookAt(playerid, 1910.7559,-1163.6423,24.9278);
	return 1;
}
public OnPlayerConnect(playerid)
{
    GetPlayerName(playerid, player_info[playerid][name], MAX_PLAYER_NAME);
    active_time[playerid] = 0.0;
	afk_seconds[playerid] = 0;
	is_afk[playerid] = false;
    player_info[playerid][admin_level] = 0;
    player_info[playerid][money] = 0;
	player_info[playerid][pLevel] = 0;
	player_info[playerid][pExp] = 0;
	player_info[playerid][pPassportID] = 0;
	player_info[playerid][pDriverLicense] = 0;
	payday_today[playerid] = false;
	exam_errors[playerid] = 0;
	exam_theory_passed[playerid] = false;
	exam_practice_started[playerid] = false;
	exam_practice_passed[playerid] = false;
	exam_checkpoint_index[playerid] = 0;
	exam_practice_timer[playerid] = 0;
	has_driver_license[playerid] = false;
	money_td[playerid] = PlayerText:INVALID_TEXT_DRAW;
	money_td_timer[playerid] = 0;
	money_td_alpha[playerid] = 255;
	last_money[playerid] = player_info[playerid][money];
	bike_rented[playerid] = false;
	rented_bike_id[playerid] = -1;
	bike_empty_time[playerid] = 0;
	player_info[playerid][pHunger] = 100;
	player_info[playerid][pThirst] = 100;
	player_info[playerid][pHealth] = 100.0;

    if(!IsValidRPName(player_info[playerid][name]))
    {
        SCM(playerid, COLOR_LIGHTRED, "Âû áûëè êèêíóòû: Âàø íèê íå ñîîòâåòñòâóåò RolePlay ôîðìàòó.");
        SCM(playerid, COLOR_WHITE, "Ôîðìàò íèêà: Èìÿ_Ôàìèëèÿ (Ïðèìåð: Ivan_Ivanov)");
        SetTimerEx("KickPlayer", 500, false, "i", playerid);
        return 1;
    }

    in_skin_select[playerid] = false;
    is_logged[playerid] = false;
    login_attempts[playerid] = 0;
    is_chatting[playerid] = false;
    SetTimerEx("GetAccountFromMysql", 1000, false, "i", playerid);
	RemoveBuildingForPlayer(playerid, 1294, 1753.7656, -1671.3125, 17.2500, 0.25);
    RemoveBuildingForPlayer(playerid, 1531, 1767.2109, -1617.5391, 15.0391, 0.25);
	RemoveBuildingForPlayer(playerid, 2786, 1968.7344, 1029.6641, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2786, 1967.4063, 1029.6563, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2786, 1968.7344, 1021.6875, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2786, 1967.4063, 1021.6875, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2786, 1968.7344, 1014.0000, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2786, 1967.4063, 1014.0000, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2786, 1968.7344, 1006.3438, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2786, 1967.4063, 1006.3438, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2786, 1941.0234, 1014.2266, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2786, 1939.6953, 1014.2188, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2786, 1941.0234, 1021.4141, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2786, 1939.6953, 1021.4141, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2786, 1941.8438, 1029.1328, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2786, 1940.5547, 1029.4766, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2786, 1942.1250, 1006.5703, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2786, 1940.8828, 1006.1094, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 1895, 1938.0469, 986.6250, 992.8828, 0.25);
	RemoveBuildingForPlayer(playerid, 1895, 1940.6875, 989.1719, 992.8828, 0.25);
	RemoveBuildingForPlayer(playerid, 2785, 1940.8828, 1006.1094, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2098, 1941.5234, 1006.3828, 993.4141, 0.25);
	RemoveBuildingForPlayer(playerid, 2785, 1942.1250, 1006.5703, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 1895, 1943.2188, 986.5234, 992.8828, 0.25);
	RemoveBuildingForPlayer(playerid, 2785, 1939.6953, 1014.2188, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2098, 1940.3906, 1014.2031, 993.4141, 0.25);
	RemoveBuildingForPlayer(playerid, 2785, 1941.0234, 1014.2266, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2785, 1939.6953, 1021.4141, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2098, 1940.3906, 1021.4141, 993.4141, 0.25);
	RemoveBuildingForPlayer(playerid, 2785, 1941.0234, 1021.4141, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2325, 1957.4453, 987.6719, 992.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2325, 1957.7188, 987.1953, 992.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 14620, 1957.9141, 991.8516, 991.8438, 0.25);
	RemoveBuildingForPlayer(playerid, 1978, 1959.3984, 1010.1172, 992.5078, 0.25);
	RemoveBuildingForPlayer(playerid, 2188, 1960.3672, 1015.6641, 992.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 14560, 1950.7969, 1017.8047, 995.9688, 0.25);
	RemoveBuildingForPlayer(playerid, 14565, 1950.8359, 1017.7578, 993.4453, 0.25);
	RemoveBuildingForPlayer(playerid, 2773, 1960.3047, 1017.9219, 992.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 2188, 1960.3672, 1020.1719, 992.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 2773, 1961.3516, 1021.4297, 992.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 2773, 1961.3750, 1014.3672, 992.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 2325, 1961.9609, 992.2031, 992.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2325, 1962.4063, 991.8750, 992.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2188, 1962.3438, 1015.6641, 992.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 2773, 1962.3750, 1017.9219, 992.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 2188, 1962.3438, 1020.1797, 992.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 2325, 1964.5703, 998.4531, 992.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2325, 1965.1016, 998.3047, 992.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 1978, 1963.7109, 1010.1172, 992.5078, 0.25);
	RemoveBuildingForPlayer(playerid, 14561, 1964.2109, 1017.8047, 998.7031, 0.25);
	RemoveBuildingForPlayer(playerid, 2785, 1967.4063, 1014.0000, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2785, 1967.4063, 1006.3438, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2098, 1968.0938, 1006.3594, 993.4063, 0.25);
	RemoveBuildingForPlayer(playerid, 2098, 1968.0938, 1013.9844, 993.4063, 0.25);
	RemoveBuildingForPlayer(playerid, 2785, 1968.7344, 1006.3438, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2785, 1968.7344, 1014.0000, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2098, 1968.0938, 1021.6797, 993.4063, 0.25);
	RemoveBuildingForPlayer(playerid, 2785, 1967.4063, 1021.6875, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2785, 1968.7344, 1021.6875, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2785, 1940.5547, 1029.4766, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2098, 1941.2188, 1029.2969, 993.4141, 0.25);
	RemoveBuildingForPlayer(playerid, 2785, 1941.8438, 1029.1328, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2800, 1936.3594, 1040.1719, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2799, 1936.3594, 1040.1719, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2800, 1940.7109, 1041.5781, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2799, 1940.7109, 1041.5781, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2800, 1944.9453, 1040.0547, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2799, 1944.9453, 1040.0547, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2773, 1957.2422, 1041.5781, 992.3672, 0.25);
	RemoveBuildingForPlayer(playerid, 2773, 1958.5469, 1039.6016, 992.3672, 0.25);
	RemoveBuildingForPlayer(playerid, 1978, 1959.3984, 1025.6953, 992.5078, 0.25);
	RemoveBuildingForPlayer(playerid, 2773, 1959.8281, 1035.0391, 992.3672, 0.25);
	RemoveBuildingForPlayer(playerid, 2773, 1959.4297, 1037.3828, 992.3672, 0.25);
	RemoveBuildingForPlayer(playerid, 1978, 1963.7109, 1025.6953, 992.5078, 0.25);
	RemoveBuildingForPlayer(playerid, 2785, 1967.4063, 1029.6563, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2098, 1968.0938, 1029.5391, 993.4063, 0.25);
	RemoveBuildingForPlayer(playerid, 2785, 1968.7344, 1029.6641, 992.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2325, 1964.5469, 1037.2813, 992.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2325, 1965.0938, 1037.3516, 992.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2800, 1936.3594, 1043.4063, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2799, 1936.3594, 1043.4063, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2800, 1936.3594, 1046.6641, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2799, 1936.3594, 1046.6641, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2800, 1940.7109, 1044.8125, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2799, 1940.7109, 1044.8125, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2800, 1940.7109, 1048.0703, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2799, 1940.7109, 1048.0703, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2800, 1944.9453, 1043.2891, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2799, 1944.9453, 1043.2891, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2800, 1944.9453, 1046.5469, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2799, 1944.9453, 1046.5469, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2773, 1949.0859, 1045.9063, 992.3672, 0.25);
	RemoveBuildingForPlayer(playerid, 2773, 1951.4297, 1045.4453, 992.3672, 0.25);
	RemoveBuildingForPlayer(playerid, 2773, 1955.5781, 1043.2188, 992.3672, 0.25);
	RemoveBuildingForPlayer(playerid, 2773, 1953.5938, 1044.5469, 992.3672, 0.25);
	RemoveBuildingForPlayer(playerid, 14619, 1957.6797, 1043.9063, 991.8438, 0.25);
	RemoveBuildingForPlayer(playerid, 2325, 1961.9219, 1043.3594, 992.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2325, 1962.3984, 1043.6328, 992.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2325, 1957.3203, 1047.9766, 992.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2800, 1938.1484, 1051.4922, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2799, 1938.1484, 1051.4922, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2800, 1941.3828, 1051.4922, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2799, 1941.3828, 1051.4922, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2800, 1936.5078, 1055.0391, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2799, 1936.5078, 1055.0391, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2800, 1939.7422, 1055.0391, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2799, 1939.7422, 1055.0391, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2800, 1944.6406, 1051.4922, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2799, 1944.6406, 1051.4922, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2325, 1957.6563, 1048.4141, 992.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2800, 1943.0000, 1055.0391, 991.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 2799, 1943.0000, 1055.0391, 991.9844, 0.25);
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    ClearSkinSelection(playerid);
    active_time[playerid] = 0.0;
    afk_seconds[playerid] = 0;
    is_afk[playerid] = false;
    at_roulette[playerid] = false;
    roulette_creating[playerid] = false;

	if(at_roulette[playerid])
	{
	    CancelSelectTextDraw(playerid);
	    TextDrawHideForPlayer(playerid, roulette_mouse_capture);
	    at_roulette[playerid] = false;
	}
	if(roulette_bet_placed[playerid])
    {
        if(IsValidObject(roulette_chip_public[playerid]))
        {
            DestroyObject(roulette_chip_public[playerid]);
        }
        roulette_bet_placed[playerid] = false;
        roulette_bet_amount[playerid] = 0;
        roulette_bet_position[playerid] = 0;
    }
    if(bike_rented[playerid])
	{
	    if(GetVehicleModel(rented_bike_id[playerid]) != 0)
	    {
	        DestroyVehicle(rented_bike_id[playerid]);
	    }
	    bike_rented[playerid] = false;
	    rented_bike_id[playerid] = -1;
	    bike_empty_time[playerid] = 0;
	}
    if(chat_bubble[playerid] != Text3D:INVALID_3DTEXT_ID)
    {
        Delete3DTextLabel(chat_bubble[playerid]);
        chat_bubble[playerid] = Text3D:INVALID_3DTEXT_ID;
    }
    if(money_td[playerid] != PlayerText:INVALID_TEXT_DRAW)
	{
	    PlayerTextDrawDestroy(playerid, money_td[playerid]);
	    KillTimer(money_td_timer[playerid]);
	}
	PlayerTextDrawDestroy(playerid, hunger_td[playerid]);
	PlayerTextDrawDestroy(playerid, thirst_td[playerid]);
	PlayerTextDrawDestroy(playerid, hunger_bg[playerid]);
	PlayerTextDrawDestroy(playerid, thirst_bg[playerid]);

   	if(is_logged[playerid])
	{
	    new Float:hp;
	    GetPlayerHealth(playerid, hp);
	    player_info[playerid][pHealth] = hp;

	    new save_query[1024];
	    if(player_info[playerid][id] != 0)
	    {
	        mysql_format(dbHandle, save_query, sizeof(save_query),
	            "UPDATE `accounts` SET \
	            `password` = '%e', \
	            `gender` = %d, \
	            `skin` = %d, \
	            `admin` = %d, \
	            `money` = %d, \
	            `level` = %d, \
	            `exp` = %d, \
	            `passport_id` = %d, \
	            `driver_license` = %d, \
	            `hunger` = %d, \
            	`thirst` = %d, \
	            `health` = %.1f \
	            WHERE `id` = %d",
	            player_info[playerid][pass],
	            player_info[playerid][gender],
	            player_info[playerid][skin],
	            player_info[playerid][admin_level],
	            player_info[playerid][money],
	            player_info[playerid][pLevel],
	            player_info[playerid][pExp],
	            player_info[playerid][pPassportID],
	            player_info[playerid][pDriverLicense],
	            player_info[playerid][pHunger],
           		 player_info[playerid][pThirst],
	            player_info[playerid][pHealth],
	            player_info[playerid][id]
	        );
	        mysql_tquery(dbHandle, save_query, "", "");
	    }
	    else
	    {
	        mysql_format(dbHandle, save_query, sizeof(save_query),
	            "INSERT INTO `accounts` \
	            (`name`, `password`, `gender`, `skin`, `admin`, `money`, `level`, `exp`, `passport_id`, `driver_license`, `hunger`, `thirst`, `health`) \
	            VALUES \
	            ('%e', '%e', %d, %d, %d, %d, %d, %d, %d, %d, %.1f)",
	            player_info[playerid][name],
	            player_info[playerid][pass],
	            player_info[playerid][gender],
	            player_info[playerid][skin],
	            player_info[playerid][admin_level],
	            player_info[playerid][money],
	            player_info[playerid][pLevel],
	            player_info[playerid][pExp],
	            player_info[playerid][pPassportID],
	            player_info[playerid][pDriverLicense],
	            player_info[playerid][pHunger],
            	player_info[playerid][pThirst],
	            player_info[playerid][pHealth]
	        );
	        mysql_tquery(dbHandle, save_query, "OnPlayerDataSaved", "i", playerid);
	    }
	}

    working_gardener[playerid] = false;
    weed_count[playerid] = 0;
    HideServerLogo(playerid);

    for(new i = 0; i < 20; i++)
    {
        if(IsValidDynamicObject(weed_objects[playerid][i]))
        {
            DestroyDynamicObject(weed_objects[playerid][i]);
        }
    }

    passport_ready[playerid] = false;
    passport_waiting[playerid] = false;
    exam_theory_passed[playerid] = false;
    exam_practice_started[playerid] = false;
    exam_practice_passed[playerid] = false;

    if(exam_practice_timer[playerid] != 0)
    {
        KillTimer(exam_practice_timer[playerid]);
        exam_practice_timer[playerid] = 0;
    }

    DisablePlayerRaceCheckpoint(playerid);
    exam_checkpoint_index[playerid] = 0;
    has_driver_license[playerid] = false;
    is_logged[playerid] = false;
    is_chatting[playerid] = false;
    player_info[playerid][id] = 0;

    return 1;
}

public OnPlayerSpawn(playerid)
{
    if(!is_logged[playerid]) return 0;

    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 1);
    SetPlayerSkin(playerid, player_info[playerid][skin]);
    SetPlayerPos(playerid, 1776.1272, -1665.2067, 14.4310);
    SetPlayerHealth(playerid, player_info[playerid][pHealth]);
    SetPlayerFacingAngle(playerid, 137.2522);
    SetCameraBehindPlayer(playerid);
    TogglePlayerControllable(playerid, 1);
    afk_seconds[playerid] = 0;
    is_afk[playerid] = false;
    last_money[playerid] = player_info[playerid][money];


    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, player_info[playerid][money]);

    ShowServerLogo(playerid);

	PlayerTextDrawShow(playerid, hunger_bg[playerid]);
	PlayerTextDrawShow(playerid, thirst_bg[playerid]);
	PlayerTextDrawShow(playerid, hunger_td[playerid]);
	PlayerTextDrawShow(playerid, thirst_td[playerid]);

    return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	return 1;
}
public OnVehicleSpawn(vehicleid)
{
    for(new i = 0; i < 3; i++)
    {
        if(vehicleid == exam_cars[i])
        {
            SetVehicleVirtualWorld(exam_cars[i], 1);
            ChangeVehicleColor(exam_cars[i], 1, 1);
            SetVehicleNumberPlate(exam_cars[i], "EXAM");
            SetVehicleParamsEx(exam_cars[i], 0, 0, 0, 0, 0, 0, 0);
            SetVehicleHealth(exam_cars[i], 1000.0);
            vehicle_engine[exam_cars[i]] = false;
            return 1;
        }
    }
    return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
    for(new i = 0; i < 3; i++)
    {
        if(vehicleid == exam_cars[i])
        {
            DestroyVehicle(vehicleid);

            switch(i)
            {
                case 0: exam_cars[i] = CreateVehicle(445, 1297.8899, -1866.3218, 13.5469, 0.0, 1, 1, 0);
                case 1: exam_cars[i] = CreateVehicle(445, 1294.8899, -1866.3218, 13.5469, 0.0, 1, 1, 0);
                case 2: exam_cars[i] = CreateVehicle(445, 1291.8899, -1866.3218, 13.5469, 0.0, 1, 1, 0);
            }

            SetVehicleVirtualWorld(exam_cars[i], 1);
            ChangeVehicleColor(exam_cars[i], 1, 1);
            SetVehicleNumberPlate(exam_cars[i], "EXAM");
            SetVehicleParamsEx(exam_cars[i], 0, 0, 0, 0, 0, 0, 0);
            SetVehicleHealth(exam_cars[i], 1000.0);
            vehicle_engine[exam_cars[i]] = false;

            return 1;
        }
    }
    return 1;
}

public OnPlayerText(playerid, text[])
{
    if(!is_logged[playerid]) return 0;
    if(in_skin_select[playerid]) return 0;
    if(text[0] == '/') return 1;

    new Float:current_time = GetTickCount();
    new Float:time_diff = (current_time - last_message_time[playerid]) / 1000.0;

    if(time_diff < 0.5)
    {
        message_count[playerid]++;
        if(message_count[playerid] >= 3) return 0;
    }
    else
    {
        message_count[playerid] = 0;
    }

    last_message_time[playerid] = current_time;

    afk_seconds[playerid] = 0;
    if(is_afk[playerid]) is_afk[playerid] = false;

    ApplyAnimation(playerid, "PED", "IDLE_CHAT", 4.1, 0, 0, 0, 0, 0, 1);
    is_chatting[playerid] = true;
    SetTimerEx("StopChatAnimTimer", 3000, false, "i", playerid);

    if(chat_bubble[playerid] != Text3D:INVALID_3DTEXT_ID)
    {
        Delete3DTextLabel(chat_bubble[playerid]);
    }

    chat_bubble[playerid] = Create3DTextLabel(text, 0xFFFFFFFF, 0.0, 0.0, 0.0, 20.0, 0, 0);
    Attach3DTextLabelToPlayer(chat_bubble[playerid], playerid, 0.0, 0.0, 0.3);
    SetTimerEx("DeleteChatBubble", 5000, false, "ii", _:chat_bubble[playerid], playerid);

    new chat_msg[144];
    format(chat_msg, sizeof(chat_msg), "%s ãîâîðèò: %s", player_info[playerid][name], text);
    new Float:chat_x, Float:chat_y, Float:chat_z;
	GetPlayerPos(playerid, chat_x, chat_y, chat_z);
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i) && IsPlayerInRangeOfPoint(i, 15.0, chat_x, chat_y, chat_z))
	    {
	        SCM(i, COLOR_WHITE, chat_msg);
	    }
	}
    return 0;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
    return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER)
    {
        new vehicleid = GetPlayerVehicleID(playerid);

        for(new i = 0; i < 3; i++)
        {
            if(vehicleid == exam_cars[i])
            {
                if(has_driver_license[playerid])
                {
                    SCM(playerid, COLOR_LIGHTRED, "- Âû óæå ñäàëè ýêçàìåí!");
                    RemovePlayerFromVehicle(playerid);
                    return 1;
                }

                if(!exam_theory_passed[playerid] || !exam_practice_started[playerid])
                {
                    if(!exam_theory_passed[playerid])
                        SCM(playerid, COLOR_LIGHTRED, "- Âû íå ñäàëè òåîðèþ! Ñíà÷àëà ñäàéòå ýêçàìåí â àâòîøêîëå.");
                    else
                        SCM(playerid, COLOR_LIGHTRED, "- Ñíà÷àëà íà÷íèòå ïðàêòè÷åñêèé ýêçàìåí ó èíñòðóêòîðà!");

                    RemovePlayerFromVehicle(playerid);
                    return 1;
                }

                SCM(playerid, COLOR_WHITE, "{FFFFFF}Íàæìèòå {FF9900}ËÅÂÛÉ CTRL{FFFFFF} ÷òîáû çàâåñòè äâèãàòåëü.");

                exam_checkpoint_index[playerid] = 0;
                SetPlayerRaceCheckpoint(playerid, 0,
                    exam_checkpoints[0][0],
                    exam_checkpoints[0][1],
                    exam_checkpoints[0][2],
                    exam_checkpoints[1][0],
                    exam_checkpoints[1][1],
                    exam_checkpoints[1][2],
                    5.0);

                return 1;
            }
        }
    }
    return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
    if(exam_practice_started[playerid] && exam_theory_passed[playerid])
    {
        new idx = exam_checkpoint_index[playerid];
        new max_checkpoints = sizeof(exam_checkpoints);

        if(IsPlayerInRangeOfPoint(playerid, 5.0,
            exam_checkpoints[idx][0],
            exam_checkpoints[idx][1],
            exam_checkpoints[idx][2]))
        {
            if(idx == max_checkpoints - 1)
            {
                KillTimer(exam_practice_timer[playerid]);
                ExamPracticePassed(playerid);
                return 1;
            }

            exam_checkpoint_index[playerid]++;
            new next = exam_checkpoint_index[playerid];

            if(next == max_checkpoints - 1)
            {
                SetPlayerRaceCheckpoint(playerid, 1,
                    exam_checkpoints[next][0],
                    exam_checkpoints[next][1],
                    exam_checkpoints[next][2],
                    0.0, 0.0, 0.0,
                    5.0);
            }
            else
            {
                SetPlayerRaceCheckpoint(playerid, 0,
                    exam_checkpoints[next][0],
                    exam_checkpoints[next][1],
                    exam_checkpoints[next][2],
                    exam_checkpoints[next + 1][0],
                    exam_checkpoints[next + 1][1],
                    exam_checkpoints[next + 1][2],
                    5.0);
            }

            if(idx == 0)
            {
                exam_practice_time[playerid] = 180;
                exam_practice_timer[playerid] = SetTimerEx("ExamPracticeTimer", 1000, true, "i", playerid);
            }
        }
    }
    return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnRconCommand(cmd[])
{
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
    if(!is_logged[playerid]) return 0;
    if(in_skin_select[playerid]) return 0;
    SetPlayerSkin(playerid, player_info[playerid][skin]);
    return 1;
}

public OnObjectMoved(objectid)
{
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}
public OnPlayerPickUpPickup(playerid, pickupid)
{
    new world = GetPlayerVirtualWorld(playerid);
    new Float:current_time = GetTickCount();

    if((current_time - last_pickup_time[playerid]) < 3000)
    {
        return 0;
    }

    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1545.6157, -1811.4038, 14.4699) && world == 1)
    {
        last_pickup_time[playerid] = current_time;

        SetPlayerVirtualWorld(playerid, 2);
        SetPlayerInterior(playerid, 1);
        SetPlayerPos(playerid, 2441.2732, -1596.4253, 3009.0859);
        SetPlayerFacingAngle(playerid, 0.0);
        SetCameraBehindPlayer(playerid);

        TogglePlayerControllable(playerid, 0);
        SetTimerEx("EnableControl", 500, false, "i", playerid);

        return 1;
    }

    if(IsPlayerInRangeOfPoint(playerid, 2.0, 2441.2732, -1596.4253, 3009.0859) && world == 2)
    {
        last_pickup_time[playerid] = current_time;

        SetPlayerVirtualWorld(playerid, 1);
        SetPlayerInterior(playerid, 0);
        SetPlayerPos(playerid, 1545.6157, -1811.4038, 14.4699);
        SetPlayerFacingAngle(playerid, 0.0);
        SetCameraBehindPlayer(playerid);

        TogglePlayerControllable(playerid, 0);
        SetTimerEx("EnableControl", 500, false, "i", playerid);

        return 1;
    }

    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1302.3058, -1868.9077, 13.5469) && world == 1)
    {
        last_pickup_time[playerid] = current_time;

        SetPlayerVirtualWorld(playerid, 3);
        SetPlayerInterior(playerid, 1);
        SetPlayerPos(playerid, 1189.4663, -1803.9528, 3001.0859);
        SetPlayerFacingAngle(playerid, 180.1143);
        SetCameraBehindPlayer(playerid);

        TogglePlayerControllable(playerid, 0);
        SetTimerEx("EnableControl", 500, false, "i", playerid);

        return 1;
    }

    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1189.4663, -1803.9528, 3001.0859) && world == 3)
    {
        last_pickup_time[playerid] = current_time;

        SetPlayerVirtualWorld(playerid, 1);
        SetPlayerInterior(playerid, 0);
        SetPlayerPos(playerid, 1302.3058, -1868.9077, 13.5469);
        SetPlayerFacingAngle(playerid, 0.0648);
        SetCameraBehindPlayer(playerid);

        TogglePlayerControllable(playerid, 0);
        SetTimerEx("EnableControl", 500, false, "i", playerid);

        return 1;
    }

	if(IsPlayerInRangeOfPoint(playerid, 2.0, 1022.4791, -1121.4207, 23.8701) && world == 1)
	{
	    last_pickup_time[playerid] = current_time;
	    SetPlayerVirtualWorld(playerid, 10);
	    SetPlayerInterior(playerid, 10);
	    SetPlayerPos(playerid, 2016.2699, 1017.1541, 996.875);
	    SetPlayerFacingAngle(playerid, 180.0);
	    SetCameraBehindPlayer(playerid);
	    TogglePlayerControllable(playerid, 0);
	    SetTimerEx("EnableControl", 500, false, "i", playerid);
	    SCM(playerid, COLOR_GREEN, "{FF9900}[Êàçèíî]{FFFFFF} Äîáðî ïîæàëîâàòü â êàçèíî ×åòûðå Äðàêîíà! Èñïîëüçóéòå /play ÷òîáû èãðàòü.");
	    return 1;
	}

	if(IsPlayerInRangeOfPoint(playerid, 2.0, 2016.2699, 1017.1541, 996.875) && world == 10)
	{
	    last_pickup_time[playerid] = current_time;
	    SetPlayerVirtualWorld(playerid, 1);
	    SetPlayerInterior(playerid, 0);
	    SetPlayerPos(playerid, 1022.4791, -1121.4207, 23.8701);
	    SetPlayerFacingAngle(playerid, 356.6537);
	    SetCameraBehindPlayer(playerid);
	    TogglePlayerControllable(playerid, 0);
	    SetTimerEx("EnableControl", 500, false, "i", playerid);
	    return 1;
	}
    return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    afk_seconds[playerid] = 0;
    if(is_afk[playerid])
    {
        is_afk[playerid] = false;
    }

    if((newkeys & KEY_FIRE) && !(oldkeys & KEY_FIRE))
    {
        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            cmd_engine(playerid, "");
            return 0;
        }
    }

    if((newkeys & KEY_ACTION) && !(oldkeys & KEY_ACTION))
    {
        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            cmd_engine(playerid, "");
            return 0;
        }
	}
 	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	return 1;
}

public OnPlayerUpdate(playerid)
{
    if(in_skin_select[playerid])
	{
	    new Float:cX, Float:cY, Float:cZ;
	    GetPlayerCameraPos(playerid, cX, cY, cZ);
	    if(cX != skin_cam_pos[playerid][0] || cY != skin_cam_pos[playerid][1] || cZ != skin_cam_pos[playerid][2])
	    {
	        SetPlayerCameraPos(playerid, skin_cam_pos[playerid][0], skin_cam_pos[playerid][1], skin_cam_pos[playerid][2]);
	        SetPlayerCameraLookAt(playerid, 386.3, 173.8, 1008.3);
	    }
	}

    if(is_chatting[playerid])
    {
        new keys, updown, leftright;
        GetPlayerKeys(playerid, keys, updown, leftright);

        if(updown != 0 || leftright != 0 || keys & KEY_SPRINT || keys & KEY_JUMP)
        {
            ClearAnimations(playerid, 1);
            is_chatting[playerid] = false;

            afk_seconds[playerid] = 0;
            if(is_afk[playerid])
            {
                is_afk[playerid] = false;
            }
        }
    }

    if(working_gardener[playerid])
    {
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);

        for(new i = 0; i < 20; i++)
        {
            if(!weed_collected[playerid][i])
            {
                if(GetPlayerDistanceFromPoint(playerid, weed_markers[i][0], weed_markers[i][1], weed_markers[i][2]) < 1.5)
                {
                    ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);

                    weed_collected[playerid][i] = true;
                    weed_count[playerid]++;

                    new msg[128];
                    format(msg, sizeof(msg), "{FF6347}%d {FFFFFF}ñîáðàíî!", weed_count[playerid]);
                    SCM(playerid, COLOR_GREEN, msg);

                    if(IsValidDynamicObject(weed_objects[playerid][i]))
                    {
                        DestroyDynamicObject(weed_objects[playerid][i]);
                    }

                    if(weed_count[playerid] >= 20)
                    {
                        SCM(playerid, COLOR_GREEN, "{FF6347}Âñå êóñòû ñîáðàíû!{FFFFFF} Ïîäîéäèòå ê ñàäîâíèêó äëÿ ïîëó÷åíèÿ îïëàòû è {FF6347}áîíóñà!!");
                        SCM(playerid, COLOR_WHITE, "{FF6347}[Ïîäñêàçêà]{FFFFFF} Èñïîëüçóéòå{33AA33} /talk{FFFFFF} ÷òîáû çàâåðøèòü ñìåíó.");
                    }

                    break;
                }
            }
        }
    }
    if(last_money[playerid] != player_info[playerid][money])
	{
	    new diff = player_info[playerid][money] - last_money[playerid];
	    if(diff != 0)
	    {
	        ShowMoneyChange(playerid, diff);
	    }
	    last_money[playerid] = player_info[playerid][money];
	}
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i) && i != playerid)
	    {
	        new Float:tx, Float:ty, Float:tz;
	        GetPlayerPos(i, tx, ty, tz);

	        new Float:distance = GetPlayerDistanceFromPoint(playerid, tx, ty, tz);

	        if(distance <= 6.0)
	        {
	            ShowPlayerNameTagForPlayer(playerid, i, 1);
	        }
	        else
	        {
	            ShowPlayerNameTagForPlayer(playerid, i, 0);
	        }
	    }
	}
    return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	new str[256];
	switch(dialogid)
	{
		case DLG_REG:
		{
			if(!response) return Kick(playerid);
			if(!(strlen(inputtext)>= 8 && strlen(inputtext) <= 22))
			{
				SCM(playerid, COLOR_LIGHTRED, "- Äëèíà ïàðîëÿ äîëæíà áûòü íå ìåíåå 8 è íå áîëåå 22 ñèìâîëîâ.");
				format(str, sizeof(str), "{FFFFFF}- Äîáðî ïîæàëîâàòü â Êàëèôîðíèþ, âèæó âû âïåðâûå â íàøåì øòàòå.\n- Ïðèäóìàé ïàðîëü, ïî íåìó òû ñìîæåøü àâòîðèçîâàòüñÿ â áóäóùåì.\n\nÒâî¸ èìÿ: %s[%i]", player_info[playerid][name], playerid);
				return SPD(playerid, DLG_REG, DIALOG_STYLE_INPUT, "{FF9900}Ðåãèñòðàöèÿ", str, "Äàëåå", "Îòìåíà");
			}
			new len = strlen(inputtext);
			for(new i = 0; i < len; i++)
			{
				switch(inputtext[i])
				{
					case 'a'..'z', 'A'..'Z', '0'..'9': continue;
					default:
					{
                        SCM(playerid, COLOR_LIGHTRED, "- Ïàðîëü ìîæåò ñîñòîÿòü èç ëàòèíñêèõ ñèìâîëîâ è öèôð.");
						format(str, sizeof(str), "{FFFFFF}- Äîáðî ïîæàëîâàòü â Êàëèôîðíèþ, âèæó âû âïåðâûå â íàøåì øòàòå.\n- Ïðèäóìàé ïàðîëü, ïî íåìó òû ñìîæåøü àâòîðèçîâàòüñÿ â áóäóùåì.\n\nÒâî¸ èìÿ: %s[%i]", player_info[playerid][name], playerid);
						return SPD(playerid, DLG_REG, DIALOG_STYLE_INPUT, "{FF9900}Ðåãèñòðàöèÿ", str, "Äàëåå", "Îòìåíà");
					}
				}
			}
			bcrypt_hash(playerid, "OnPasswordHashed", inputtext, BCRYPT_COST);
		}
		case DLG_REG_GENDER:
		{
			if(!response)
			{
				player_info[playerid][gender] = 2;
				format(str, sizeof(str), "{FFFFFF}- Ïîäðóãà, ñ òàêîé ïðè÷åñêîé íà òåáÿ íå ïîñìîòðèò äàæå èçâðàùåíåö â ïàðêå.\n- Äàâàé ñìåíèì èìèäæ?");
				SPD(playerid, DLG_REG_SKIN, DIALOG_STYLE_MSGBOX, "{FF9900}Ðåãèñòðàöèÿ", str, "Äàâàé", "");
			}
			else
			{
                player_info[playerid][gender] = 1;
		        format(str, sizeof(str), "{FFFFFF}- Ìäà... òåáå áû ïåðåîäåòüñÿ ïàðåíü, à òî íà ðàéîíå òåáÿ íå ïîéìóò.\n- Äàâàé ñìåíèì èìèäæ?");
		        SPD(playerid, DLG_REG_SKIN, DIALOG_STYLE_MSGBOX, "{FF9900}Ðåãèñòðàöèÿ", str, "Äàâàé", "");
			}
			return 1;
		}
		case DLG_REG_SKIN:
		{
		    if(!response) return 1;
		    StartSkinSelection(playerid);
		    return 1;
		}
		case DLG_LOGIN:
		{
		    if(!response) return Kick(playerid);

		    if(strlen(inputtext) == 0)
		    {
		        format(str, sizeof(str), "{FFFFFF}- Òû çàðåãèñòðèðîâàí, ââåäè ñâîé ïàðîëü.\n\nÒâî¸ èìÿ: %s[%i]", player_info[playerid][name], playerid);
		        return SPD(playerid, DLG_LOGIN, DIALOG_STYLE_PASSWORD, "{FF9900}Àâòîðèçàöèÿ", str, "Âîéòè", "Îòìåíà");
		    }

		    bcrypt_verify(playerid, "OnPasswordChecked", inputtext, player_info[playerid][pass]);
		    return 1;
		}
		case 1001:
		{
		    if(response)
		    {
		        format(str, sizeof(str), "{FFFFFF}- Íàø ïàðê çàðîñ, çà îäèí ñîðâàííûé êóñò ïëà÷ó òåáå $1, ñïðàâèøüñÿ?");
		        ShowPlayerDialog(playerid, 1002, DIALOG_STYLE_MSGBOX, "{FF9900}Ñàäîâíèê", str, "Äà", "Îòìåíà");
		    }
		    return 1;
		}
		case 1002:
		{
		    if(response)
		    {
		        working_gardener[playerid] = true;
		        weed_count[playerid] = 0;

		        for(new i = 0; i < 20; i++)
		        {
		            weed_collected[playerid][i] = false;

		            weed_objects[playerid][i] = CreateDynamicObject(823,
		                weed_markers[i][0], weed_markers[i][1], weed_markers[i][2],
		                0.0, 0.0, 0.0, 1, 0, playerid, 9999.0);
		        }

		        SCM(playerid, COLOR_GREEN, "{FF9900}[Ñàäîâíèê]{FFFFFF} Îòëè÷íî! Ñîðâè âñå êóñòû â ýòîì ïàðêå!");
		    }
		    return 1;
		}
		case 1003:
		{
		    if(response)
		    {
		        new payment = weed_count[playerid];

		        if(weed_count[playerid] >= 20)
		        {
		            payment += 20;
		        }

		        player_info[playerid][money] += payment;
		        UpdatePlayerMoney(playerid);
		        SavePlayerData(playerid);

		        if(weed_count[playerid] >= 20)
		        {
		            new msg[128];
		            format(msg, sizeof(msg), "{FF9900}[Ñàäîâíèê]{FFFFFF} Îòëè÷íî! Âû ñîðâàëè âñå êóñòû è ïîëó÷àåòå $%d ($%d çà êóñòû + $20 áîíóñ)!", payment, weed_count[playerid]);
		            SCM(playerid, COLOR_GREEN, msg);
		        }
		        else
		        {
		            new msg[128];
		            format(msg, sizeof(msg), "{FF9900}[Ñàäîâíèê]{FFFFFF} Âû ñîðâàëè %d êóñòîâ è ïîëó÷àåòå $%d!", weed_count[playerid], payment);
		            SCM(playerid, COLOR_GREEN, msg);
		        }

		        working_gardener[playerid] = false;
		        weed_count[playerid] = 0;

		        for(new i = 0; i < 20; i++)
		        {
		            if(IsValidDynamicObject(weed_objects[playerid][i]))
		            {
		                DestroyDynamicObject(weed_objects[playerid][i]);
		            }
		            weed_collected[playerid][i] = false;
		        }

		        SCM(playerid, COLOR_WHITE, "{FF6347}[Ïîäñêàçêà]{FFFFFF} Ìîæåøü ñíîâà ïîãîâîðèòü ñ ñàäîâíèêîì äëÿ íîâîé ñìåíû.");
		    }
		    return 1;
		}
		case 2003:
		{
		    if(response)
		    {
		        if(player_info[playerid][money] < 3)
		        {
		            SCM(playerid, COLOR_LIGHTRED, "- Ó âàñ íåäîñòàòî÷íî äåíåã! Íóæíî 3$.");
		            return 1;
		        }

		        player_info[playerid][money] -= 3;
		        UpdatePlayerMoney(playerid);
		        SavePlayerData(playerid);

		        passport_waiting[playerid] = true;

		        format(str, sizeof(str), "{FFFFFF}- Çàìå÷àòåëüíî, îæèäàéòå, ÿ âàñ ïîçîâó.");
		        ShowPlayerDialog(playerid, 2004, DIALOG_STYLE_MSGBOX, "{FF9900}Ïàñïîðòèñòêà", str, "Îê", "");
		    }
		    return 1;
		}
		case 2004:
		{
		    SetTimerEx("PassportReady", 10000, false, "i", playerid);
		    return 1;
		}
		case 2005:
		{
		    return 1;
		}
		case 3001:
		{
		    if(response)
		    {
		        format(str, sizeof(str), "{FFFFFF}- Äëÿ íà÷àëà âàì íóæíî ñäàòü òåîðèþ, äåðæèòå êíèãó!\n\n{FF9900}Ñòîèìîñòü ýêçàìåíà: $8.");
		        ShowPlayerDialog(playerid, 3002, DIALOG_STYLE_MSGBOX, "{FF9900}Èíñòðóêòîð", str, "Äàëåå", "Îòìåíà");
		    }
		    return 1;
		}
		case 3002:
		{
		    if(response)
		    {
		        if(player_info[playerid][money] < 8)
		            return SCM(playerid, COLOR_LIGHTRED, "- Ó âàñ íåäîñòàòî÷íî äåíåã! Íóæíî $8.");

		        player_info[playerid][money] -= 8;
		        UpdatePlayerMoney(playerid);
		        SavePlayerData(playerid);

		        exam_errors[playerid] = 0;

		        format(str, sizeof(str),
		            "{FF9900}1. {FFFFFF}Ñëåâà\n\
		            {FF9900}2. {FFFFFF}Ñïðàâà\n\
		            {FF9900}3. {FFFFFF}Ñ ëþáîé");
		        ShowPlayerDialog(playerid, 3010, DIALOG_STYLE_LIST, "{FF9900}(1/8) Ñ êàêîé ñòîðîíû ðàçðåø¸í îáãîí?", str, "Îòâåòèòü", "");
		    }
		    return 1;
		}
		case 3010:
		{
		    if(!response) return ExamFailed(playerid);
		    if(listitem != 0) { exam_errors[playerid]++; }
		    if(exam_errors[playerid] >= 2) return ExamFailed(playerid);

		    format(str, sizeof(str),
		        "{FF9900}1. {FFFFFF}Äà, âñåãäà\n\
		        {FF9900}2. {FFFFFF}Íåò\n\
		        {FF9900}3. {FFFFFF}Òîëüêî â ýêñòðåííûõ ñëó÷àÿõ");
		    ShowPlayerDialog(playerid, 3011, DIALOG_STYLE_LIST, "{FF9900}(2/8) Ìîæíî ëè ïàðêîâàòüñÿ íà òðîòóàðå?", str, "Îòâåòèòü", "");
		    return 1;
		}
		case 3011:
		{
		    if(!response) return ExamFailed(playerid);
		    if(listitem != 1) { exam_errors[playerid]++; }
		    if(exam_errors[playerid] >= 2) return ExamFailed(playerid);

		    format(str, sizeof(str),
		        "{FF9900}1. {FFFFFF}60 êì/÷\n\
		        {FF9900}2. {FFFFFF}80 êì/÷\n\
		        {FF9900}3. {FFFFFF}100 êì/÷");
		    ShowPlayerDialog(playerid, 3012, DIALOG_STYLE_LIST, "{FF9900}(3/8) Ìàêñèìàëüíàÿ ñêîðîñòü â ãîðîäå?", str, "Îòâåòèòü", "");
		    return 1;
		}
		case 3012:
		{
		    if(!response) return ExamFailed(playerid);
		    if(listitem != 0) { exam_errors[playerid]++; }
		    if(exam_errors[playerid] >= 2) return ExamFailed(playerid);

		    format(str, sizeof(str),
		        "{FF9900}1. {FFFFFF}Äà, âñåãäà\n\
		        {FF9900}2. {FFFFFF}Íåò\n\
		        {FF9900}3. {FFFFFF}Òîëüêî íà òðàññå");
		    ShowPlayerDialog(playerid, 3013, DIALOG_STYLE_LIST, "{FF9900}(4/8) Íóæíî ëè ïðèñò¸ãèâàòü ðåìåíü áåçîïàñíîñòè?", str, "Îòâåòèòü", "");
		    return 1;
		}
		case 3013:
		{
		    if(!response) return ExamFailed(playerid);
		    if(listitem != 0) { exam_errors[playerid]++; }
		    if(exam_errors[playerid] >= 2) return ExamFailed(playerid);

		    format(str, sizeof(str),
		        "{FF9900}1. {FFFFFF}Äà, åñëè íåìíîãî\n\
		        {FF9900}2. {FFFFFF}Íåò\n\
		        {FF9900}3. {FFFFFF}Òîëüêî äí¸ì");
		    ShowPlayerDialog(playerid, 3014, DIALOG_STYLE_LIST, "{FF9900}(5/8) Ìîæíî ëè óïðàâëÿòü àâòî â íåòðåçâîì âèäå?", str, "Îòâåòèòü", "");
		    return 1;
		}
		case 3014:
		{
		    if(!response) return ExamFailed(playerid);
		    if(listitem != 1) { exam_errors[playerid]++; }
		    if(exam_errors[playerid] >= 2) return ExamFailed(playerid);

		    format(str, sizeof(str),
		        "{FF9900}1. {FFFFFF}Ïðîåçä ðàçðåø¸í\n\
		        {FF9900}2. {FFFFFF}Ñòîï\n\
		        {FF9900}3. {FFFFFF}Ïðèãîòîâèòüñÿ");
		    ShowPlayerDialog(playerid, 3015, DIALOG_STYLE_LIST, "{FF9900}(6/8) ×òî îçíà÷àåò êðàñíûé ñèãíàë ñâåòîôîðà?", str, "Îòâåòèòü", "");
		    return 1;
		}
		case 3015:
		{
		    if(!response) return ExamFailed(playerid);
		    if(listitem != 1) { exam_errors[playerid]++; }
		    if(exam_errors[playerid] >= 2) return ExamFailed(playerid);

		    format(str, sizeof(str),
		        "{FF9900}1. {FFFFFF}15 ìåòðîâ\n\
		        {FF9900}2. {FFFFFF}30 ìåòðîâ\n\
		        {FF9900}3. {FFFFFF}50 ìåòðîâ");
		    ShowPlayerDialog(playerid, 3016, DIALOG_STYLE_LIST, "{FF9900}(7/8) Íà êàêîì ðàññòîÿíèè ñòàâèòü àâàðèéíûé çíàê?", str, "Îòâåòèòü", "");
		    return 1;
		}
		case 3016:
		{
		    if(!response) return ExamFailed(playerid);
		    if(listitem != 1) { exam_errors[playerid]++; }
		    if(exam_errors[playerid] >= 2) return ExamFailed(playerid);

		    format(str, sizeof(str),
		        "{FF9900}1. {FFFFFF}Äà\n\
		        {FF9900}2. {FFFFFF}Íåò\n\
		        {FF9900}3. {FFFFFF}Åñëè íåò ïåøåõîäîâ");
		    ShowPlayerDialog(playerid, 3017, DIALOG_STYLE_LIST, "{FF9900}(8/8) Ðàçðåøåíî ðàçâîðà÷èâàòüñÿ íà ïåø. ïåðåõîäå?", str, "Îòâåòèòü", "");
		    return 1;
		}
		case 3017:
		{
		    if(!response) return ExamFailed(playerid);
		    if(listitem != 1) { exam_errors[playerid]++; }

		    if(exam_errors[playerid] >= 2) return ExamFailed(playerid);

		    exam_theory_passed[playerid] = true;
		    SCM(playerid, COLOR_GREEN, "{FF9900}[Ýêçàìåí] Ïîçäðàâëÿåì! Òåîðåòè÷åñêàÿ ÷àñòü ñäàíà! Ïîãîâîðèòå ñ èíñòðóêòîðîì äëÿ ïðîäîëæåíèÿ.");
		    return 1;
		}
		case 3099:
		{
		    return 1;
		}
		case 3100:
		{
		    if(response)
		    {
		        exam_practice_started[playerid] = true;
		        SCM(playerid, COLOR_GREEN, "{FF9900}[Ýêçàìåí] Ïðàêòè÷åñêèé ýêçàìåí íà÷àëñÿ!");
		        SCM(playerid, COLOR_WHITE, "{FFFFFF}Âûéäèòå èç àâòîøêîëû è ñÿäüòå â áåëóþ ìàøèíó ó çäàíèÿ.");
		    }
		    return 1;
		}
		case 4001:
		{
		    if(!response) return 1;

		    if(!at_roulette[playerid]) return 1;

		    if(roulette_bet_placed[playerid])
		    {
		        SCM(playerid, COLOR_LIGHTRED, "[Ðóëåòêà] Âû óæå ñäåëàëè ñòàâêó! Äîæäèòåñü çàâåðøåíèÿ ðàóíäà.");
		        return 1;
		    }

		    new amount = strval(inputtext);
		    new pos = roulette_chip_position[playerid];

		    if(amount < 100)
		    return SCM(playerid, COLOR_LIGHTRED, "[Ðóëåòêà] Ìèíèìàëüíàÿ ñòàâêà: $100!");

			if(amount > 1000)
		    return SCM(playerid, COLOR_LIGHTRED, "[Ðóëåòêà] Ìàêñèìàëüíàÿ ñòàâêà: $1,000!");

		    if(player_info[playerid][money] < amount)
		        return SCM(playerid, COLOR_LIGHTRED, "[Ðóëåòêà] Ó âàñ íåäîñòàòî÷íî äåíåã!");

		    player_info[playerid][money] -= amount;
		    UpdatePlayerMoney(playerid);
		    ShowMoneyChange(playerid, -amount);
		    SavePlayerData(playerid);

		    roulette_bet_amount[playerid] = amount;
		    roulette_bet_position[playerid] = pos;
		    roulette_bet_placed[playerid] = true;

		    new chip_models[] = {1901, 1902, 1903, 1904};
		    new random_model = chip_models[random(sizeof(chip_models))];

		    roulette_chip_public[playerid] = CreateObject(random_model,
			    roulette_chip_positions[pos][0],
			    roulette_chip_positions[pos][1],
			    roulette_chip_positions[pos][2],
			    0.0, 0.0, 0.0, 50.0);

		    Roul_DestroyTD(playerid);
		    at_roulette[playerid] = false;

		    format(str, sizeof(str), "{FF9900}[Ðóëåòêà] {FFFFFF}Èãðîê %s ñòàâèò {33AA33}%d$", player_info[playerid][name], amount, pos);
		    SendRouletteMessage(COLOR_YELLOW, str);

		    if(!roulette_round_started)
		    {
		        roulette_round_started = true;
		        roulette_countdown = 15;
		        croupier_played = false;
		        roulette_timer = SetTimer("RouletteCountdown", 1000, true);
		        UpdateRouletteTimer3D(roulette_countdown);
		    }
		    return 1;
		}
		case 4002:
		{
		    return 1;
		}
		case 6001:
		{
		    if(!response) return 1;

		    if(player_info[playerid][pLevel] >= 3)
		    {
		        if(player_info[playerid][money] < 3)
		            return SCM(playerid, COLOR_LIGHTRED, "[Ïðîêàò÷èê] Ó âàñ íåäîñòàòî÷íî äåíåã! Íóæíî 3$.");

		        player_info[playerid][money] -= 3;
		        UpdatePlayerMoney(playerid);
		        SavePlayerData(playerid);
		    }

		    new Float:x, Float:y, Float:z, Float:a;
		    GetPlayerPos(playerid, x, y, z);
		    GetPlayerFacingAngle(playerid, a);

		    new bikeid = CreateVehicle(510, x + 2.0, y, z, a, -1, -1, 0);
		    SetVehicleVirtualWorld(bikeid, GetPlayerVirtualWorld(playerid));
		    SetVehiclePos(bikeid, 1757.0920, -1674.3387, 13.2);
		    SetVehicleZAngle(bikeid, 93.0551);

		    bike_rented[playerid] = true;
		    rented_bike_id[playerid] = bikeid;
		    bike_empty_time[playerid] = 0;

		    SetTimerEx("PutInBike", 200, false, "ii", playerid, bikeid);

		    SCM(playerid, COLOR_GREEN, "{FF9900}[Ïðîêàò÷èê] {FFFFFF}Âû àðåíäîâàëè âåëîñèïåä! Õîðîøåãî ïóòè!");
		}
		case 7001:
		{
		    if(!response) return 1;

		    if(player_info[playerid][pLevel] >= 3)
		    {
		        if(player_info[playerid][money] < 5)
		            return SCM(playerid, COLOR_LIGHTRED, "[Ïðîäàâåö] Ó âàñ íåäîñòàòî÷íî äåíåã! Íóæíî 5$.");

		        player_info[playerid][money] -= 5;
		        UpdatePlayerMoney(playerid);
		    }

		    player_info[playerid][pHunger] = 100;
		    player_info[playerid][pThirst] = 100;

		    new Float:hp;
		    GetPlayerHealth(playerid, hp);
		    new Float:new_hp = hp + 20.0;
		    if(new_hp > 100.0) new_hp = 100.0;
		    SetPlayerHealth(playerid, new_hp);
		    player_info[playerid][pHealth] = new_hp;

		    SavePlayerData(playerid);

		    PlayerTextDrawTextSize(playerid, hunger_td[playerid], 500.0 + (100.0 * player_info[playerid][pHunger] / 100.0), 0.0);
		    PlayerTextDrawShow(playerid, hunger_td[playerid]);
		    PlayerTextDrawTextSize(playerid, thirst_td[playerid], 500.0 + (100.0 * player_info[playerid][pThirst] / 100.0), 0.0);
		    PlayerTextDrawShow(playerid, thirst_td[playerid]);

		    SCM(playerid, COLOR_GREEN, "[Ïðîäàâåö] Ïðèÿòíîãî àïïåòèòà! Çäîðîâüå, ãîëîä è æàæäà âîññòàíîâëåíû.");
		    ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
		    return 1;
		}
	}
	return 1;
}
forward PutInBike(playerid, bikeid);
public PutInBike(playerid, bikeid)
{
    if(IsPlayerConnected(playerid) && GetVehicleModel(bikeid) != 0)
    {
        PutPlayerInVehicle(playerid, bikeid, 0);
        SetVehiclePos(bikeid, 1757.0920, -1674.3387, 13.2);
    }
    return 1;
}
forward CheckEmptyBikes();
public CheckEmptyBikes()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i) && bike_rented[i])
        {
            new vehicleid = rented_bike_id[i];

            if(GetVehicleModel(vehicleid) != 0)
            {
                new has_driver = 0;
                for(new j = 0; j < MAX_PLAYERS; j++)
                {
                    if(IsPlayerConnected(j) && GetPlayerVehicleID(j) == vehicleid && GetPlayerState(j) == PLAYER_STATE_DRIVER)
                    {
                        has_driver = 1;
                        break;
                    }
                }

                if(!has_driver)
                {
                    bike_empty_time[i] += 1;

                    if(bike_empty_time[i] >= 3)
                    {
                        DestroyVehicle(vehicleid);
                        bike_rented[i] = false;
                        rented_bike_id[i] = -1;
                        bike_empty_time[i] = 0;
                    }
                }
                else
                {
                    bike_empty_time[i] = 0;
                }
            }
            else
            {
                bike_rented[i] = false;
                rented_bike_id[i] = -1;
                bike_empty_time[i] = 0;
            }
        }
    }
    return 1;
}
public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return 1;
}

public OnPlayerClickMap(playerid, Float: fX, Float: fY, Float: fZ)
{
    if(player_info[playerid][admin_level] < 1) return 0;

    SetPlayerPos(playerid, fX, fY, fZ);

    new msg[128];
    format(msg, sizeof(msg), "Àäìèíèñòðàòîð %s òåëåïîðòèðîâàëñÿ ïî êàðòå", player_info[playerid][name]);
    SendAdminMessage(COLOR_GREEN, msg);

    return 1;
}

forward GetAccountFromMysql(playerid);
public GetAccountFromMysql(playerid)
{
    mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `accounts` WHERE `name` = '%e'", player_info[playerid][name]);
    mysql_tquery(dbHandle, query, "CheckAccountFromMysql", "i", playerid);
}

forward CheckAccountFromMysql(playerid);
public CheckAccountFromMysql(playerid)
{
	new str[256];
	if(cache_num_rows() == 0)
	{
	    format(str, sizeof(str), "{FFFFFF}- Äîáðî ïîæàëîâàòü â Êàëèôîðíèþ, âèæó âû âïåðâûå â íàøåì øòàòå.\n- Ïðèäóìàé ïàðîëü, ïî íåìó òû ñìîæåøü àâòîðèçîâàòüñÿ â áóäóùåì.\n\nÒâî¸ èìÿ: %s[%i]", player_info[playerid][name], playerid);
		SPD(playerid, DLG_REG, DIALOG_STYLE_INPUT, "{FF9900}Ðåãèñòðàöèÿ", str, "Äàëåå", "Îòìåíà");
	}
	else
	{
	    cache_get_value_name(0, "password", player_info[playerid][pass], 61);

	    format(str, sizeof(str), "{FFFFFF}- Òû çàðåãèñòðèðîâàí, ââåäè ñâîé ïàðîëü.\n\nÒâî¸ èìÿ: %s[%i]", player_info[playerid][name], playerid);
		SPD(playerid, DLG_LOGIN, DIALOG_STYLE_PASSWORD, "{FF9900}Àâòîðèçàöèÿ", str, "Âîéòè", "Îòìåíà");
	}
}

forward OnPlayerDataLoaded(playerid);
public OnPlayerDataLoaded(playerid)
{
    if(cache_num_rows() > 0)
    {
        cache_get_value_name_int(0, "gender", player_info[playerid][gender]);
        cache_get_value_name_int(0, "skin", player_info[playerid][skin]);
        cache_get_value_name_int(0, "id", player_info[playerid][id]);
        cache_get_value_name_int(0, "admin", player_info[playerid][admin_level]);
        cache_get_value_name_int(0, "money", player_info[playerid][money]);
        cache_get_value_name_int(0, "level", player_info[playerid][pLevel]);
        cache_get_value_name_int(0, "exp", player_info[playerid][pExp]);
        cache_get_value_name_int(0, "passport_id", player_info[playerid][pPassportID]);
        cache_get_value_name_int(0, "driver_license", player_info[playerid][pDriverLicense]);
        cache_get_value_name_float(0, "health", player_info[playerid][pHealth]);
        if(player_info[playerid][pHealth] <= 0.0)
		{
		    player_info[playerid][pHealth] = 100.0;
		}

        if(player_info[playerid][pDriverLicense] == 1)
        {
            has_driver_license[playerid] = true;
        }

        SetPlayerSkin(playerid, player_info[playerid][skin]);

        cache_get_value_name_int(0, "hunger", player_info[playerid][pHunger]);
        cache_get_value_name_int(0, "thirst", player_info[playerid][pThirst]);

        if(player_info[playerid][pHunger] == 0 && player_info[playerid][pThirst] == 0)
        {
            player_info[playerid][pHunger] = 100;
            player_info[playerid][pThirst] = 100;
        }
        if(player_info[playerid][pHealth] == 0.0)
		{
		    player_info[playerid][pHealth] = 100.0;
		}

		hunger_bg[playerid] = CreatePlayerTextDraw(playerid, 498.0, 103.0, "_");
		PlayerTextDrawLetterSize(playerid, hunger_bg[playerid], 0.0001, 0.85);
		PlayerTextDrawTextSize(playerid, hunger_bg[playerid], 602.0, 0.0);
		PlayerTextDrawAlignment(playerid, hunger_bg[playerid], 1);
		PlayerTextDrawColor(playerid, hunger_bg[playerid], 0x00000088);
		PlayerTextDrawUseBox(playerid, hunger_bg[playerid], 1);
		PlayerTextDrawBoxColor(playerid, hunger_bg[playerid], 0x00000088);
		PlayerTextDrawBackgroundColor(playerid, hunger_bg[playerid], 0x00000088);
		PlayerTextDrawFont(playerid, hunger_bg[playerid], 1);
		PlayerTextDrawSetProportional(playerid, hunger_bg[playerid], 1);
		PlayerTextDrawSetShadow(playerid, hunger_bg[playerid], 0);
		PlayerTextDrawSetOutline(playerid, hunger_bg[playerid], 0);

		thirst_bg[playerid] = CreatePlayerTextDraw(playerid, 498.0, 113.0, "_");
		PlayerTextDrawLetterSize(playerid, thirst_bg[playerid], 0.0001, 0.85);
		PlayerTextDrawTextSize(playerid, thirst_bg[playerid], 602.0, 0.0);
		PlayerTextDrawAlignment(playerid, thirst_bg[playerid], 1);
		PlayerTextDrawColor(playerid, thirst_bg[playerid], 0x00000088);
		PlayerTextDrawUseBox(playerid, thirst_bg[playerid], 1);
		PlayerTextDrawBoxColor(playerid, thirst_bg[playerid], 0x00000088);
		PlayerTextDrawBackgroundColor(playerid, thirst_bg[playerid], 0x00000088);
		PlayerTextDrawFont(playerid, thirst_bg[playerid], 1);
		PlayerTextDrawSetProportional(playerid, thirst_bg[playerid], 1);
		PlayerTextDrawSetShadow(playerid, thirst_bg[playerid], 0);
		PlayerTextDrawSetOutline(playerid, thirst_bg[playerid], 0);

		hunger_td[playerid] = CreatePlayerTextDraw(playerid, 500.0, 105.0, "_");
		PlayerTextDrawLetterSize(playerid, hunger_td[playerid], 0.0001, 0.45);
		PlayerTextDrawTextSize(playerid, hunger_td[playerid], 500.0 + (100.0 * player_info[playerid][pHunger] / 100.0), 0.0);
		PlayerTextDrawAlignment(playerid, hunger_td[playerid], 1);
		PlayerTextDrawColor(playerid, hunger_td[playerid], 0x8B4513FF);
		PlayerTextDrawUseBox(playerid, hunger_td[playerid], 1);
		PlayerTextDrawBoxColor(playerid, hunger_td[playerid], 0x8B4513FF);
		PlayerTextDrawBackgroundColor(playerid, hunger_td[playerid], 0x8B4513FF);
		PlayerTextDrawFont(playerid, hunger_td[playerid], 1);
		PlayerTextDrawSetProportional(playerid, hunger_td[playerid], 1);
		PlayerTextDrawSetShadow(playerid, hunger_td[playerid], 0);
		PlayerTextDrawSetOutline(playerid, hunger_td[playerid], 0);

		thirst_td[playerid] = CreatePlayerTextDraw(playerid, 500.0, 115.0, "_");
		PlayerTextDrawLetterSize(playerid, thirst_td[playerid], 0.0001, 0.45);
		PlayerTextDrawTextSize(playerid, thirst_td[playerid], 500.0 + (100.0 * player_info[playerid][pThirst] / 100.0), 0.0);
		PlayerTextDrawAlignment(playerid, thirst_td[playerid], 1);
		PlayerTextDrawColor(playerid, thirst_td[playerid], 0x1E90FFFF);
		PlayerTextDrawUseBox(playerid, thirst_td[playerid], 1);
		PlayerTextDrawBoxColor(playerid, thirst_td[playerid], 0x1E90FFFF);
		PlayerTextDrawBackgroundColor(playerid, thirst_td[playerid], 0x1E90FFFF);
		PlayerTextDrawFont(playerid, thirst_td[playerid], 1);
		PlayerTextDrawSetProportional(playerid, thirst_td[playerid], 1);
		PlayerTextDrawSetShadow(playerid, thirst_td[playerid], 0);
		PlayerTextDrawSetOutline(playerid, thirst_td[playerid], 0);

		PlayerTextDrawShow(playerid, hunger_bg[playerid]);
		PlayerTextDrawShow(playerid, thirst_bg[playerid]);
		PlayerTextDrawShow(playerid, hunger_td[playerid]);
		PlayerTextDrawShow(playerid, thirst_td[playerid]);

        ShowServerLogo(playerid);

        if(player_info[playerid][admin_level] > 0)
        {
            new msg[128];
            format(msg, sizeof(msg), "{FF9900}Âû âîøëè êàê àäìèíèñòðàòîð óðîâíÿ %d!", player_info[playerid][admin_level]);
            SCM(playerid, COLOR_GREEN, msg);
        }
    }

    return 1;
}

stock SavePlayerData(playerid)
{
    new save_query[1024];

    if(player_info[playerid][id] != 0)
    {
        mysql_format(dbHandle, save_query, sizeof(save_query),
            "UPDATE `accounts` SET \
            `password` = '%e', \
            `gender` = %d, \
            `skin` = %d, \
            `admin` = %d, \
            `money` = %d, \
            `level` = %d, \
            `exp` = %d, \
            `passport_id` = %d, \
            `driver_license` = %d, \
            `hunger` = %d, \
            `thirst` = %d, \
            `health` = %.1f \
            WHERE `id` = %d",
            player_info[playerid][pass],
            player_info[playerid][gender],
            player_info[playerid][skin],
            player_info[playerid][admin_level],
            player_info[playerid][money],
            player_info[playerid][pLevel],
            player_info[playerid][pExp],
            player_info[playerid][pPassportID],
            player_info[playerid][pDriverLicense],
            player_info[playerid][pHunger],
            player_info[playerid][pThirst],
            player_info[playerid][pHealth],
            player_info[playerid][id]
        );

        mysql_tquery(dbHandle, save_query, "", "");
    }
    else
    {
        mysql_format(dbHandle, save_query, sizeof(save_query),
            "INSERT INTO `accounts` \
            (`name`, `password`, `gender`, `skin`, `admin`, `money`, `level`, `exp`, `passport_id`, `driver_license`, `hunger`, `thirst`, `health`) \
            VALUES \
            ('%e', '%e', %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %.1f)",
            player_info[playerid][name],
            player_info[playerid][pass],
            player_info[playerid][gender],
            player_info[playerid][skin],
            player_info[playerid][admin_level],
            player_info[playerid][money],
            player_info[playerid][pLevel],
            player_info[playerid][pExp],
            player_info[playerid][pPassportID],
            player_info[playerid][pDriverLicense],
            player_info[playerid][pHunger],
            player_info[playerid][pThirst],
            player_info[playerid][pHealth]
        );

        mysql_tquery(dbHandle, save_query, "OnPlayerDataSaved", "i", playerid);
    }

    return 1;
}
forward UpdateHungerAndThirst();
public UpdateHungerAndThirst()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i) && is_logged[i])
        {
            if(player_info[i][pHunger] > 0)
            {
                player_info[i][pHunger]--;
            }

            if(player_info[i][pThirst] > 0)
            {
                player_info[i][pThirst]--;
            }

			PlayerTextDrawTextSize(i, hunger_td[i], 500.0 + (100.0 * player_info[i][pHunger] / 100.0), 0.0);
			PlayerTextDrawShow(i, hunger_td[i]);

			PlayerTextDrawTextSize(i, thirst_td[i], 500.0 + (100.0 * player_info[i][pThirst] / 100.0), 0.0);
			PlayerTextDrawShow(i, thirst_td[i]);

            SavePlayerData(i);
        }
    }
    return 1;
}

forward HungerDamage();
public HungerDamage()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i) && is_logged[i])
        {
            new Float:hp;
            GetPlayerHealth(i, hp);

            if(player_info[i][pHunger] <= 0 && player_info[i][pThirst] <= 0)
            {
                SetPlayerHealth(i, hp - 2.0);
                player_info[i][pHealth] = hp - 2.0;
            }
            else if(player_info[i][pHunger] <= 0 || player_info[i][pThirst] <= 0)
            {
                SetPlayerHealth(i, hp - 1.0);
                player_info[i][pHealth] = hp - 1.0;
            }
        }
    }
    return 1;
}
forward OnPlayerDataSaved(playerid);
public OnPlayerDataSaved(playerid)
{
    if(player_info[playerid][id] == 0)
    {
        player_info[playerid][id] = cache_insert_id();
    }
    return 1;
}

forward SyncPayDay();
public SyncPayDay()
{
    new hour, minute, second;
    gettime(hour, minute, second);

    if(minute == 0 && second == 0)
    {
        PayDay();
    }
    return 1;
}

forward PayDay();
public PayDay()
{
    new msg[256];
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i) && is_logged[i])
        {
            if(active_time[i] >= 20.0)
            {
                GivePlayerExp(i, 1);

                new exp_needed = (player_info[i][pLevel] + 1) * 2;
                new exp_left = exp_needed - player_info[i][pExp];
                if(exp_left < 0) exp_left = 0;

                format(msg, sizeof(msg), "{FFFFFF}Âû ïîëó÷èëè {FF6347}1{FFFFFF} î÷êî îïûòà!");
                SCM(i, COLOR_GREEN, msg);

                SavePlayerData(i);
            }
            else
            {
                format(msg, sizeof(msg), "{FFFFFF}Âû íå ïîëó÷èëè {FF6347}EXP{FFFFFF}! Âû îòûãðàëè ñëèøêîì ìàëî.");
                SCM(i, COLOR_GREEN, msg);
            }

            active_time[i] = 0.0;
        }
    }
    print("[PayDay] Íà÷èñëåíèå îïûòà çàâåðøåíî!");
    return 1;
}

stock GivePlayerExp(playerid, amount)
{
    player_info[playerid][pExp] += amount;

    new exp_needed = (player_info[playerid][pLevel] + 1) * 2;

    while(player_info[playerid][pExp] >= exp_needed)
    {
        player_info[playerid][pExp] -= exp_needed;
        player_info[playerid][pLevel]++;

        new msg[128];
        format(msg, sizeof(msg), "{FF9900}Ïîçäðàâëÿåì! Âû äîñòèãëè %d óðîâíÿ!", player_info[playerid][pLevel]);
        SCM(playerid, COLOR_GREEN, msg);

        exp_needed = (player_info[playerid][pLevel] + 1) * 2;
    }

    SavePlayerData(playerid);
    return 1;
}
forward PassportReady(playerid);
public PassportReady(playerid)
{
    passport_ready[playerid] = true;
    passport_waiting[playerid] = false;

    new msg[128];
    format(msg, sizeof(msg), "{FF9900}[Ïàñïîðòèñòêà] %s, âàø ïàñïîðò ãîòîâ, ïîäîéäèòå ÷òîáû çàáðàòü.", player_info[playerid][name]);
    SCM(playerid, COLOR_GREEN, msg);
    return 1;
}
forward LoadLastPassportID();
public LoadLastPassportID()
{
    if(cache_num_rows() > 0)
    {
        cache_get_value_index_int(0, 0, LastPassportID);
        if(LastPassportID < 100000) LastPassportID = 100000;
        printf("[Ïàñïîðò] Çàãðóæåí ïîñëåäíèé íîìåð: #%d", LastPassportID);
    }
    else
    {
        printf("[Ïàñïîðò] Áàçà ïóñòà, íà÷èíàåì ñ #%d", LastPassportID);
    }
    return 1;
}
forward CheckActiveTime();
public CheckActiveTime()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i) && is_logged[i])
        {
            new keys, updown, leftright;
            GetPlayerKeys(i, keys, updown, leftright);

            if(updown != 0 || leftright != 0 ||
               keys & KEY_SPRINT || keys & KEY_JUMP ||
               keys & KEY_SECONDARY_ATTACK || keys & KEY_ACTION ||
               keys & KEY_WALK || keys & KEY_HANDBRAKE ||
               keys & KEY_FIRE || keys & KEY_LOOK_LEFT || keys & KEY_LOOK_RIGHT ||
               keys & KEY_LOOK_BEHIND)
            {
                afk_seconds[i] = 0;
                is_afk[i] = false;
            }
            else
            {
                afk_seconds[i] += 10;

                if(afk_seconds[i] >= 300 && !is_afk[i])
                {
                    is_afk[i] = true;
                }
            }

            if(!is_afk[i])
            {
                active_time[i] += 10.0 / 60.0;
            }
        }
    }
    return 1;
}
forward RouletteCountdown();
public RouletteCountdown()
{
    roulette_countdown--;

    if(roulette_countdown > 0)
    {
        UpdateRouletteTimer3D(roulette_countdown);

        if(roulette_countdown <= 2 && !croupier_played)
        {
            croupier_played = true;
            ApplyActorAnimation(roul_npc, "DEALER", "DEALER_DEAL", 4.1, 0, 0, 0, 0, 0);
        }
    }
    else
    {
        KillTimer(roulette_timer);
        roulette_timer = -1;

        Update3DTextLabelText(roulette_timer_3d, 0xFFFFFFFF, " ");

        roulette_spinning = 1;
        roulette_round_started = false;

        SendRouletteMessage(COLOR_YELLOW, "{FF9900}[Ðóëåòêà] {FFFFFF}Ñòàâêè ñäåëàíû, ñòàâîê áîëüøå íåò!");

        roulette_spin_angle = 0.0;
        roulette_spin_count = 0;
        roulette_spin_timer = SetTimer("SpinRouletteWheel", 100, true);

		roulette_number_index = 0;
		roulette_number_timer = SetTimer("SpinNumberDisplay", 80, true);
		TextDrawShowForAll(roulette_number_td);
    }
    return 1;
}
forward RouletteResult();
public RouletteResult()
{
    new str[256];
    format(str, sizeof(str), "{FF9900}[Ðóëåòêà] {FFFFFF}Âûïàëî ÷èñëî: {33AA33}%d{FFFFFF}!", roulette_winner_number);
    SendRouletteMessage(COLOR_YELLOW, str);

    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i) && roulette_bet_placed[i])
        {
            new pos = roulette_bet_position[i];
            new amount = roulette_bet_amount[i];
            new multiplier = GetRouletteMultiplier(pos, roulette_winner_number);

            if(multiplier > 0)
			{
			    new win_amount = amount * multiplier;
			    player_info[i][money] += win_amount;
			    UpdatePlayerMoney(i);
			    SavePlayerData(i);

			    format(str, sizeof(str), "{FF9900}[Ðóëåòêà] {FFFFFF}Ïîçäðàâëÿåì! Âû âûèãðàëè {33AA33}$%d{FFFFFF}!", win_amount);
			    SCM(i, COLOR_GREEN, str);

			    ApplyAnimation(i, "CASINO", "ROULETTE_WIN", 4.1, 0, 0, 0, 0, 0, 1);
			    SetTimerEx("ClearPlayerAnim", 3000, false, "i", i);
			}
			else
			{
			    SCM(i, COLOR_LIGHTRED, "[Ðóëåòêà] Ê ñîæàëåíèþ, âû ïðîèãðàëè.");

			    ApplyAnimation(i, "CASINO", "ROULETTE_LOSE", 4.1, 0, 0, 0, 0, 0, 1);
			    SetTimerEx("ClearPlayerAnim", 3000, false, "i", i);
			}

            if(IsValidObject(roulette_chip_public[i]))
            {
                DestroyObject(roulette_chip_public[i]);
            }

            roulette_bet_placed[i] = false;
            roulette_bet_amount[i] = 0;
            roulette_bet_position[i] = 0;
        }
    }

    roulette_spinning = 0;
    roulette_winner_number = -1;
    SendRouletteMessage(COLOR_YELLOW, "{FF9900}[Ðóëåòêà] {FFFFFF}Èãðà îêîí÷åíà, ïðèíèìàþòñÿ íîâûå ñòàâêè!");
    return 1;
}
forward SpinRouletteWheel();
public SpinRouletteWheel()
{
    roulette_spin_count++;
    roulette_spin_angle += 20.0;

    if(roulette_spin_angle >= 360.0)
        roulette_spin_angle -= 360.0;

    if(IsValidObject(roulette_wheel_object))
    {
        DestroyObject(roulette_wheel_object);
    }

    roulette_wheel_object = CreateObject(1979, 1945.33325, 1007.72662, 992.51978, 0.0, 0.0, 137.01343 + roulette_spin_angle);

	if(roulette_spin_count >= 50)
	{
	    KillTimer(roulette_spin_timer);
	    KillTimer(roulette_number_timer);

	    roulette_spinning = 0;
	    roulette_spin_count = 0;
	    roulette_spin_angle = 0.0;
	    croupier_played = false;

	    ClearActorAnimations(roul_npc);
	    ApplyActorAnimation(roul_npc, "DEALER", "DEALER_IDLE", 4.1, 1, 0, 0, 0, 0);

	    if(IsValidObject(roulette_wheel_object))
	        DestroyObject(roulette_wheel_object);
	    roulette_wheel_object = CreateObject(1979, 1945.33325, 1007.72662, 992.51978, 0.0, 0.0, 137.01343);

	    roulette_winner_number = random(37);

	    roulette_display_number = roulette_winner_number;
	    roulette_display_alpha = 255.0;

	    new outline_color;
		new color = GetNumberColor(roulette_display_number, outline_color);

	    new str[8];
		format(str, sizeof(str), "%d", roulette_display_number);
		TextDrawSetString(roulette_number_td, str);
		TextDrawColor(roulette_number_td, color);
		TextDrawBackgroundColor(roulette_number_td, outline_color);
		TextDrawShowForAll(roulette_number_td);

	    roulette_display_timer = SetTimer("FadeNumberDisplay", 200, true);

	    SetTimer("RouletteResult", 1, false);
	}
    return 1;
}
forward FadeNumberDisplay();
public FadeNumberDisplay()
{
    roulette_display_alpha -= 15.0;

    if(roulette_display_alpha <= 0)
    {
        KillTimer(roulette_display_timer);
        TextDrawHideForAll(roulette_number_td);
        return 1;
    }

    new number = roulette_display_number;
    new outline_color;
    new base_color = GetNumberColor(number, outline_color);

    new r = (base_color >> 24) & 0xFF;
    new g = (base_color >> 16) & 0xFF;
    new b = (base_color >> 8) & 0xFF;
    new a = floatround(roulette_display_alpha);

    new new_color = (r << 24) | (g << 16) | (b << 8) | a;
    TextDrawColor(roulette_number_td, new_color);
    TextDrawShowForAll(roulette_number_td);

    return 1;
}
forward SaveHealthTimer();
public SaveHealthTimer()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i) && is_logged[i])
        {
            new Float:hp;
            GetPlayerHealth(i, hp);

            if(player_info[i][pHealth] != hp)
            {
                player_info[i][pHealth] = hp;

                new save_query[256];
                mysql_format(dbHandle, save_query, sizeof(save_query),
                    "UPDATE `accounts` SET `health` = %.1f WHERE `id` = %d",
                    player_info[i][pHealth],
                    player_info[i][id]
                );
                mysql_tquery(dbHandle, save_query, "", "");
            }
        }
    }
    return 1;
}
//==================ñòîêè===================
stock GivePlayerMoneyEx(playerid, amount)
{
    player_info[playerid][money] += amount;
    UpdatePlayerMoney(playerid);
    SavePlayerData(playerid);
    return 1;
}
stock ShowServerLogo(playerid)
{
    if(!logo_shown[playerid])
    {
        TextDrawShowForPlayer(playerid, LOGO_TD[0]);
        TextDrawShowForPlayer(playerid, LOGO_TD[1]);
        logo_shown[playerid] = true;
    }
    return 1;
}

stock HideServerLogo(playerid)
{
    if(logo_shown[playerid])
    {
        TextDrawHideForPlayer(playerid, LOGO_TD[0]);
        TextDrawHideForPlayer(playerid, LOGO_TD[1]);
        logo_shown[playerid] = false;
    }
    return 1;
}

stock StartSkinSelection(playerid)
{
    in_skin_select[playerid] = true;
    player_skin_index[playerid] = 0;

    skin_cam_pos[playerid][0] = 390.0;
    skin_cam_pos[playerid][1] = 173.8;
    skin_cam_pos[playerid][2] = 1008.8;

    new vw = playerid + 1000;

    SetPlayerVirtualWorld(playerid, vw);
    SetPlayerInterior(playerid, 3);
    SetPlayerPos(playerid, 386.30, 173.80, 1008.38);
    SetPlayerFacingAngle(playerid, 270.0);
    SetPlayerCameraPos(playerid, 390.0, 173.8, 1008.8);
    SetPlayerCameraLookAt(playerid, 386.3, 173.8, 1008.3);
    TogglePlayerControllable(playerid, 0);

    new skinid;
    if(player_info[playerid][gender] == 1)
        skinid = male_skins[0];
    else
        skinid = female_skins[0];

    SetPlayerSkin(playerid, skinid);

    CreateSkinTD(playerid);

    return 1;
}

stock UpdatePlayerSkin(playerid)
{
    UpdatePreviewActor(playerid);
}

stock CreateSkinTD(playerid)
{
    btn_left[playerid] = CreatePlayerTextDraw(playerid, 260.0, 300.0, "PREV");
    PlayerTextDrawLetterSize(playerid, btn_left[playerid], 0.40, 1.60);
    PlayerTextDrawTextSize(playerid, btn_left[playerid], 50.0, 30.0);
    PlayerTextDrawAlignment(playerid, btn_left[playerid], 2);
    PlayerTextDrawColor(playerid, btn_left[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, btn_left[playerid], 1);
    PlayerTextDrawBoxColor(playerid, btn_left[playerid], 0x00000088);
    PlayerTextDrawFont(playerid, btn_left[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, btn_left[playerid], 1);
    PlayerTextDrawShow(playerid, btn_left[playerid]);

    btn_right[playerid] = CreatePlayerTextDraw(playerid, 390.0, 300.0, "NEXT");
    PlayerTextDrawLetterSize(playerid, btn_right[playerid], 0.40, 1.60);
    PlayerTextDrawTextSize(playerid, btn_right[playerid], 50.0, 30.0);
    PlayerTextDrawAlignment(playerid, btn_right[playerid], 2);
    PlayerTextDrawColor(playerid, btn_right[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, btn_right[playerid], 1);
    PlayerTextDrawBoxColor(playerid, btn_right[playerid], 0x00000088);
    PlayerTextDrawFont(playerid, btn_right[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, btn_right[playerid], 1);
    PlayerTextDrawShow(playerid, btn_right[playerid]);

    btn_select[playerid] = CreatePlayerTextDraw(playerid, 325.0, 370.0, "SELECT");
    PlayerTextDrawLetterSize(playerid, btn_select[playerid], 0.45, 1.80);
    PlayerTextDrawTextSize(playerid, btn_select[playerid], 80.0, 30.0);
    PlayerTextDrawAlignment(playerid, btn_select[playerid], 2);
    PlayerTextDrawColor(playerid, btn_select[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, btn_select[playerid], 1);
    PlayerTextDrawBoxColor(playerid, btn_select[playerid], 0xFF9900FF);
    PlayerTextDrawFont(playerid, btn_select[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, btn_select[playerid], 1);
    PlayerTextDrawShow(playerid, btn_select[playerid]);

    SelectTextDraw(playerid, 0xFF9900FF);
}

stock DestroySkinTD(playerid)
{
    CancelSelectTextDraw(playerid);
    PlayerTextDrawDestroy(playerid, btn_left[playerid]);
    PlayerTextDrawDestroy(playerid, btn_right[playerid]);
    PlayerTextDrawDestroy(playerid, btn_select[playerid]);
}

stock ClearSkinSelection(playerid)
{
    if(in_skin_select[playerid])
    {
        DestroySkinTD(playerid);
        CancelSelectTextDraw(playerid);
        in_skin_select[playerid] = false;
    }
}

stock IsValidRPName(const nick[])
{
    new underscore_count = 0;
    new len = strlen(nick);

    if(len < 5 || len > 20) return 0;

    for(new i = 0; i < len; i++)
    {
        if(!((nick[i] >= 'A' && nick[i] <= 'Z') || (nick[i] >= 'a' && nick[i] <= 'z') || nick[i] == '_'))
        {
            return 0;
        }

        if(nick[i] == '_')
        {
            underscore_count++;
        }
    }

    if(underscore_count != 1) return 0;

    if(nick[0] == '_' || nick[len - 1] == '_') return 0;

    new underscore_pos = strfind(nick, "_");
    if(underscore_pos != -1)
    {
        if(nick[underscore_pos + 1] >= 'a' && nick[underscore_pos + 1] <= 'z')
        {
            return 0;
        }
    }

    if(nick[0] >= 'a' && nick[0] <= 'z')
    {
        return 0;
    }

    new repeat_count = 0;
    for(new i = 1; i < len; i++)
    {
        if(nick[i] == nick[i-1] && nick[i] != '_')
        {
            repeat_count++;
            if(repeat_count >= 3) return 0;
        }
        else
        {
            repeat_count = 0;
        }
    }

    new bad_words[][] = {
        "Admin", "Moder", "Server", "Owner", "Player", "Goverment",
        "FBI", "CIA", "Police", "SWAT", "Army", "Military",
        "President", "Mayor", "Governor", "SAMP"
    };

    for(new i = 0; i < sizeof(bad_words); i++)
    {
        if(strfind(nick, bad_words[i], true) != -1)
        {
            return 0;
        }
    }

    return 1;
}
stock ShowMoneyChange(playerid, amount)
{
    if(money_td[playerid] != PlayerText:INVALID_TEXT_DRAW)
    {
        PlayerTextDrawDestroy(playerid, money_td[playerid]);
        KillTimer(money_td_timer[playerid]);
    }

    new str[32];

    if(amount > 0)
    {
        format(str, sizeof(str), "+$%d", amount);
        money_td_color[playerid] = 0x33AA33AA;
    }
    else
    {
        format(str, sizeof(str), "-$%d", -amount);
        money_td_color[playerid] = 0xFF0000AA;
    }

    money_td[playerid] = CreatePlayerTextDraw(playerid, 500.0, 350.0, str);
    PlayerTextDrawLetterSize(playerid, money_td[playerid], 0.80, 3.20);
    PlayerTextDrawAlignment(playerid, money_td[playerid], 2);
    PlayerTextDrawColor(playerid, money_td[playerid], money_td_color[playerid]);
    PlayerTextDrawSetOutline(playerid, money_td[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, money_td[playerid], 0x00000088);
    PlayerTextDrawFont(playerid, money_td[playerid], 2);
    PlayerTextDrawSetProportional(playerid, money_td[playerid], 1);
    PlayerTextDrawSetShadow(playerid, money_td[playerid], 0);
    PlayerTextDrawShow(playerid, money_td[playerid]);

    money_td_alpha[playerid] = 255;

    KillTimer(money_td_timer[playerid]);
    money_td_timer[playerid] = SetTimerEx("FadeMoneyTD", 100, true, "i", playerid);
    return 1;
}
forward FadeMoneyTD(playerid);
public FadeMoneyTD(playerid)
{
    money_td_alpha[playerid] -= 8;

    if(money_td_alpha[playerid] <= 0)
    {
        KillTimer(money_td_timer[playerid]);
        PlayerTextDrawDestroy(playerid, money_td[playerid]);
        money_td[playerid] = PlayerText:INVALID_TEXT_DRAW;
        return 1;
    }

    new color = money_td_color[playerid];

    new r = (color >> 24) & 0xFF;
    new g = (color >> 16) & 0xFF;
    new b = (color >> 8) & 0xFF;

    new new_color = (r << 24) | (g << 16) | (b << 8) | money_td_alpha[playerid];
    PlayerTextDrawColor(playerid, money_td[playerid], new_color);
    PlayerTextDrawShow(playerid, money_td[playerid]);

    return 1;
}
stock CheckAdminLevel(playerid, level)
{
    if(player_info[playerid][admin_level] >= level)
        return 1;
    return 0;
}

stock SendAdminMessage(color, const message[])
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i) && player_info[i][admin_level] > 0)
        {
            SCM(i, color, message);
        }
    }
    return 1;
}

stock UpdatePlayerMoney(playerid)
{
    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, player_info[playerid][money]);
    return 1;
}
stock StartExamPractice(playerid)
{
    exam_practice_started[playerid] = true;
    exam_checkpoint_index[playerid] = 0;

    SCM(playerid, COLOR_GREEN, "{FF9900}[Ýêçàìåí] Ïðàêòè÷åñêèé ýêçàìåí íà÷àëñÿ!");
    SCM(playerid, COLOR_WHITE, "{FFFFFF}Âûéäèòå èç àâòîøêîëû, ñÿäüòå â áåëóþ ìàøèíó è ñëåäóéòå ïî ìàðêåðàì. Íà ïðîõîæäåíèå äà¸òñÿ 3 ìèíóòû!");
    return 1;
}

stock ExamPracticePassed(playerid)
{
    DisablePlayerRaceCheckpoint(playerid);

    new vehicleid = GetPlayerVehicleID(playerid);
    if(vehicleid != 0)
    {
        for(new i = 0; i < 3; i++)
        {
            if(vehicleid == exam_cars[i])
            {
                RemovePlayerFromVehicle(playerid);
                SetVehicleToRespawn(vehicleid);
                break;
            }
        }
    }

    exam_practice_started[playerid] = false;
    exam_theory_passed[playerid] = false;
    exam_checkpoint_index[playerid] = 0;
    exam_practice_passed[playerid] = true;

    SCM(playerid, COLOR_GREEN, "{FF9900}[Ýêçàìåí] Ïðàêòè÷åñêèé ýêçàìåí óñïåøíî ïðîéäåí!");
    SCM(playerid, COLOR_WHITE, "{FFFFFF}Ïðîéäèòå â àâòîøêîëó äëÿ ïîëó÷åíèÿ âîäèòåëüñêèõ ïðàâ.");

    return 1;
}
stock ExamPracticeFailed(playerid)
{
    KillTimer(exam_practice_timer[playerid]);
    DisablePlayerRaceCheckpoint(playerid);

    exam_practice_started[playerid] = false;
    exam_theory_passed[playerid] = false;
    exam_checkpoint_index[playerid] = 0;
    exam_practice_passed[playerid] = false;

    SCM(playerid, COLOR_LIGHTRED, "{FF9900}[Ýêçàìåí] Âû ïðîâàëèëè ïðàêòè÷åñêèé ýêçàìåí! Âðåìÿ âûøëî.");
    SCM(playerid, COLOR_WHITE, "{FFFFFF}Ïîäîéäèòå ê èíñòðóêòîðó äëÿ ïåðåñäà÷è.");

    return 1;
}
stock ExamFailed(playerid)
{
    SCM(playerid, COLOR_LIGHTRED, "{FF9900}[Ýêçàìåí] Âû ïðîâàëèëè òåîðèþ! (2 îøèáêè)");
    SCM(playerid, COLOR_WHITE, "{FFFFFF}Ïîäîéäèòå ê èíñòðóêòîðó äëÿ ïåðåñäà÷è.");
    exam_errors[playerid] = 0;
    return 1;
}
public ExamPracticeTimer(playerid)
{
    exam_practice_time[playerid]--;

    if(exam_practice_time[playerid] <= 0)
    {
        ExamPracticeFailed(playerid);
    }

    return 1;
}
public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(clickedid == Text:INVALID_TEXT_DRAW)
    {
        if(roulette_creating[playerid])
        {
            return 1;
        }

        if(at_roulette[playerid])
        {
            Roul_DestroyTD(playerid);
            at_roulette[playerid] = false;
            return 1;
        }

        if(in_skin_select[playerid])
        {
            SelectTextDraw(playerid, 0xFF9900FF);
            return 1;
        }

        return 0;
    }

    if(clickedid == roulette_mouse_capture)
    {
        return 1;
    }
    return 0;
}
stock UpdateRouletteTimer3D(seconds)
{
    new str[128];
    format(str, sizeof(str), "{FF9900}Ñòàâêà ñäåëàíà!\n{FFFFFF}Äî ñòàðòà èãðû: {FF6347}%d {FFFFFF}ñåêóíä", seconds);
    Update3DTextLabelText(roulette_timer_3d, 0xFFFFFFFF, str);
    return 1;
}
stock GetRouletteMultiplier(bet_pos, winner_number)
{
    if(bet_pos >= 0 && bet_pos <= 36)
    {
        if(bet_pos == 0 && winner_number == 0) return 36;
        if(bet_pos == winner_number) return 36;
        return 0;
    }

    if(bet_pos == 40)
    {
        if(winner_number >= 1 && winner_number <= 12) return 3;
        return 0;
    }

    if(bet_pos == 41)
    {
        if(winner_number >= 13 && winner_number <= 24) return 3;
        return 0;
    }

    if(bet_pos == 42)
    {
        if(winner_number >= 25 && winner_number <= 36) return 3;
        return 0;
    }

    if(bet_pos == 43)
    {
        if(winner_number >= 1 && winner_number <= 18) return 2;
        return 0;
    }

    if(bet_pos == 44)
    {
        if(winner_number > 0 && winner_number % 2 == 0) return 2;
        return 0;
    }

    if(bet_pos == 45)
    {
        if(IsRedNumber(winner_number)) return 2;
        return 0;
    }

    if(bet_pos == 46)
    {
        if(winner_number > 0 && !IsRedNumber(winner_number)) return 2;
        return 0;
    }

    if(bet_pos == 47)
    {
        if(winner_number > 0 && winner_number % 2 != 0) return 2;
        return 0;
    }

    if(bet_pos == 48)
    {
        if(winner_number >= 19 && winner_number <= 36) return 2;
        return 0;
    }

    return 0;
}

stock IsRedNumber(number)
{
    new red_numbers[] = {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};
    for(new i = 0; i < sizeof(red_numbers); i++)
    {
        if(number == red_numbers[i]) return 1;
    }
    return 0;
}
// ========== ÔÓÍÊÖÈÈ ÐÓËÅÒÊÈ ==========
stock Roul_CreateTD(playerid)
{
    roulette_exit_td[playerid] = CreatePlayerTextDraw(playerid, 594.3334, 347.2149, "EXIT");
    PlayerTextDrawLetterSize(playerid, roulette_exit_td[playerid], 0.4000, 1.6000);
    PlayerTextDrawTextSize(playerid, roulette_exit_td[playerid], 622.0, 10.0);
    PlayerTextDrawAlignment(playerid, roulette_exit_td[playerid], 1);
    PlayerTextDrawColor(playerid, roulette_exit_td[playerid], -1);
    PlayerTextDrawUseBox(playerid, roulette_exit_td[playerid], 1);
    PlayerTextDrawBoxColor(playerid, roulette_exit_td[playerid], -1523963137);
    PlayerTextDrawBackgroundColor(playerid, roulette_exit_td[playerid], 255);
    PlayerTextDrawFont(playerid, roulette_exit_td[playerid], 1);
    PlayerTextDrawSetProportional(playerid, roulette_exit_td[playerid], 1);
    PlayerTextDrawSetShadow(playerid, roulette_exit_td[playerid], 0);
    PlayerTextDrawSetSelectable(playerid, roulette_exit_td[playerid], 1);
    PlayerTextDrawShow(playerid, roulette_exit_td[playerid]);

    casinoo_PTD[playerid][0] = CreatePlayerTextDraw(playerid, 341.6666, 54.3555, ">>");
    PlayerTextDrawLetterSize(playerid, casinoo_PTD[playerid][0], 0.4000, 1.6000);
    PlayerTextDrawTextSize(playerid, casinoo_PTD[playerid][0], 361.0, 10.0);
    PlayerTextDrawAlignment(playerid, casinoo_PTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, casinoo_PTD[playerid][0], -1);
    PlayerTextDrawUseBox(playerid, casinoo_PTD[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, casinoo_PTD[playerid][0], -5963521);
    PlayerTextDrawBackgroundColor(playerid, casinoo_PTD[playerid][0], 255);
    PlayerTextDrawFont(playerid, casinoo_PTD[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, casinoo_PTD[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, casinoo_PTD[playerid][0], 0);
    PlayerTextDrawSetSelectable(playerid, casinoo_PTD[playerid][0], 1);
    PlayerTextDrawShow(playerid, casinoo_PTD[playerid][0]);

    casinoo_PTD[playerid][1] = CreatePlayerTextDraw(playerid, 271.9999, 53.9407, "<<");
    PlayerTextDrawLetterSize(playerid, casinoo_PTD[playerid][1], 0.4000, 1.6000);
    PlayerTextDrawTextSize(playerid, casinoo_PTD[playerid][1], 292.0, 10.0);
    PlayerTextDrawAlignment(playerid, casinoo_PTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, casinoo_PTD[playerid][1], -1);
    PlayerTextDrawUseBox(playerid, casinoo_PTD[playerid][1], 1);
    PlayerTextDrawBoxColor(playerid, casinoo_PTD[playerid][1], -5963521);
    PlayerTextDrawBackgroundColor(playerid, casinoo_PTD[playerid][1], 255);
    PlayerTextDrawFont(playerid, casinoo_PTD[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, casinoo_PTD[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, casinoo_PTD[playerid][1], 0);
    PlayerTextDrawSetSelectable(playerid, casinoo_PTD[playerid][1], 1);
    PlayerTextDrawShow(playerid, casinoo_PTD[playerid][1]);

    casinoo_PTD[playerid][2] = CreatePlayerTextDraw(playerid, 308.6666, 26.1481, "UP");
    PlayerTextDrawLetterSize(playerid, casinoo_PTD[playerid][2], 0.4000, 1.6000);
    PlayerTextDrawTextSize(playerid, casinoo_PTD[playerid][2], 326.0, 10.0);
    PlayerTextDrawAlignment(playerid, casinoo_PTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, casinoo_PTD[playerid][2], -1);
    PlayerTextDrawUseBox(playerid, casinoo_PTD[playerid][2], 1);
    PlayerTextDrawBoxColor(playerid, casinoo_PTD[playerid][2], -5963521);
    PlayerTextDrawBackgroundColor(playerid, casinoo_PTD[playerid][2], 255);
    PlayerTextDrawFont(playerid, casinoo_PTD[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, casinoo_PTD[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, casinoo_PTD[playerid][2], 0);
    PlayerTextDrawSetSelectable(playerid, casinoo_PTD[playerid][2], 1);
    PlayerTextDrawShow(playerid, casinoo_PTD[playerid][2]);

    casinoo_PTD[playerid][3] = CreatePlayerTextDraw(playerid, 295.6666, 95.0073, "DOWN");
    PlayerTextDrawLetterSize(playerid, casinoo_PTD[playerid][3], 0.4000, 1.6000);
    PlayerTextDrawTextSize(playerid, casinoo_PTD[playerid][3], 338.0, 10.0);
    PlayerTextDrawAlignment(playerid, casinoo_PTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, casinoo_PTD[playerid][3], -1);
    PlayerTextDrawUseBox(playerid, casinoo_PTD[playerid][3], 1);
    PlayerTextDrawBoxColor(playerid, casinoo_PTD[playerid][3], -5963521);
    PlayerTextDrawBackgroundColor(playerid, casinoo_PTD[playerid][3], 255);
    PlayerTextDrawFont(playerid, casinoo_PTD[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, casinoo_PTD[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, casinoo_PTD[playerid][3], 0);
    PlayerTextDrawSetSelectable(playerid, casinoo_PTD[playerid][3], 1);
    PlayerTextDrawShow(playerid, casinoo_PTD[playerid][3]);

    casinoo_PTD[playerid][4] = CreatePlayerTextDraw(playerid, 584.3331, 290.8000, "SELECT");
    PlayerTextDrawLetterSize(playerid, casinoo_PTD[playerid][4], 0.4000, 1.6000);
    PlayerTextDrawTextSize(playerid, casinoo_PTD[playerid][4], 626.0, 10.0);
    PlayerTextDrawAlignment(playerid, casinoo_PTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, casinoo_PTD[playerid][4], -1);
    PlayerTextDrawUseBox(playerid, casinoo_PTD[playerid][4], 1);
    PlayerTextDrawBoxColor(playerid, casinoo_PTD[playerid][4], 8388863);
    PlayerTextDrawBackgroundColor(playerid, casinoo_PTD[playerid][4], 255);
    PlayerTextDrawFont(playerid, casinoo_PTD[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, casinoo_PTD[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, casinoo_PTD[playerid][4], 0);
    PlayerTextDrawSetSelectable(playerid, casinoo_PTD[playerid][4], 1);
    PlayerTextDrawShow(playerid, casinoo_PTD[playerid][4]);

    roulette_chip_object[playerid] = CreatePlayerObject(playerid, 2992,
        roulette_chip_positions[0][0],
        roulette_chip_positions[0][1],
        roulette_chip_positions[0][2] + 0.3,
        0.0, 0.0, 0.0);
    roulette_chip_position[playerid] = 0;
    roulette_chip_created[playerid] = true;

    TextDrawShowForPlayer(playerid, roulette_mouse_capture);
    SelectTextDraw(playerid, 0xFF9900FF);

    return 1;
}
stock Roul_HideTD(playerid)
{
    PlayerTextDrawHide(playerid, roulette_exit_td[playerid]);
    for(new i = 0; i < 5; i++)
        PlayerTextDrawHide(playerid, casinoo_PTD[playerid][i]);
    return 1;
}

stock Roul_ShowTD(playerid)
{
    PlayerTextDrawShow(playerid, roulette_exit_td[playerid]);
    for(new i = 0; i < 5; i++)
        PlayerTextDrawShow(playerid, casinoo_PTD[playerid][i]);
    SelectTextDraw(playerid, 0xFF9900FF);
    return 1;
}

stock Roul_DestroyTD(playerid)
{
    if(IsValidPlayerObject(playerid, roulette_chip_object[playerid]))
	{
	    DestroyPlayerObject(playerid, roulette_chip_object[playerid]);
	}
	roulette_chip_created[playerid] = false;

    CancelSelectTextDraw(playerid);
    TextDrawHideForPlayer(playerid, roulette_mouse_capture);

    PlayerTextDrawDestroy(playerid, roulette_exit_td[playerid]);
    for(new i = 0; i < 5; i++)
        PlayerTextDrawDestroy(playerid, casinoo_PTD[playerid][i]);

    SetCameraBehindPlayer(playerid);

    return 1;
}
stock GetNumberColor(number, &outline_color)
{
    if(number == 0)
    {
        outline_color = 0x000000FF;
        return 0x00FF00FF;
    }

    if(IsRedNumber(number))
    {
        outline_color = 0x000000FF;
        return 0xFF0000FF;
    }
    else
    {
        outline_color = 0xFFFFFFFF;
        return 0x000000FF;
    }
}
stock SendRouletteMessage(color, const message[])
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i) && GetPlayerVirtualWorld(i) == 10 && IsPlayerInRangeOfPoint(i, 5.0, 1946.68030, 1007.92188, 992.50983))
        {
            SCM(i, color, message);
        }
    }
    return 1;
}
CMD:play(playerid, params[])
{
    if(GetPlayerVirtualWorld(playerid) == 10)
    {
        if(roulette_bet_placed[playerid])
        {
            SCM(playerid, COLOR_LIGHTRED, "[Ðóëåòêà] Âû óæå ñäåëàëè ñòàâêó! Äîæäèòåñü çàâåðøåíèÿ ðàóíäà.");
            return 1;
        }

        if(roulette_spinning == 1)
        {
            SCM(playerid, COLOR_LIGHTRED, "[Ðóëåòêà] Èãðà óæå èä¸ò! Äîæäèòåñü ñëåäóþùåãî ðàóíäà.");
            return 1;
        }
        if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1946.68030, 1007.92188, 992.50983))
            return SCM(playerid, COLOR_LIGHTRED, "- Âû íå çà èãðàëüíûì ñòîëîì!");

        if(at_roulette[playerid])
            return SCM(playerid, COLOR_LIGHTRED, "- Âû óæå ñèäèòå çà ñòîëîì!");

        GetPlayerCameraPos(playerid, roulette_cam_save[playerid][3], roulette_cam_save[playerid][4], roulette_cam_save[playerid][5]);

        GetPlayerPos(playerid, roulette_cam_save[playerid][0], roulette_cam_save[playerid][1], roulette_cam_save[playerid][2]);

        roulette_creating[playerid] = true;

        CancelSelectTextDraw(playerid);

        at_roulette[playerid] = true;

        SetPlayerCameraPos(playerid, 1946.5700, 1007.7200, 996.4400);
        SetPlayerCameraLookAt(playerid, 1946.5700, 1008.5200, 992.5098);

        Roul_CreateTD(playerid);

        SetTimerEx("RouletteCreationDone", 500, false, "i", playerid);

        return 1;
    }
    SCM(playerid, COLOR_LIGHTRED, "- Âû íå â êàçèíî!");
    return 1;
}
stock MoveRouletteChip(playerid, newposition)
{
    if(!roulette_chip_created[playerid]) return 0;

    if(IsValidPlayerObject(playerid, roulette_chip_object[playerid]))
    {
        SetPlayerObjectPos(playerid, roulette_chip_object[playerid],
            roulette_chip_positions[newposition][0],
            roulette_chip_positions[newposition][1],
            roulette_chip_positions[newposition][2] + 0.3);
    }
    else
    {
        roulette_chip_object[playerid] = CreatePlayerObject(playerid, 2992,
            roulette_chip_positions[newposition][0],
            roulette_chip_positions[newposition][1],
            roulette_chip_positions[newposition][2] + 0.3,
            0.0, 0.0, 0.0);
    }

    roulette_chip_position[playerid] = newposition;
    return 1;
}
//================================================
forward SetPlayerSkinDelayed(playerid, skinid);
public SetPlayerSkinDelayed(playerid, skinid)
{
    SetPlayerSkin(playerid, skinid);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 1);
    return 1;
}

forward DeleteChatBubble(Text3D:bubble, playerid);
public DeleteChatBubble(Text3D:bubble, playerid)
{
    if(chat_bubble[playerid] == bubble)
    {
        Delete3DTextLabel(bubble);
        chat_bubble[playerid] = Text3D:INVALID_3DTEXT_ID;
    }
    return 1;
}

forward KickPlayer(playerid);
public KickPlayer(playerid)
{
    Kick(playerid);
    return 1;
}
forward CreateRouletteChip(playerid);
public CreateRouletteChip(playerid)
{
    if(!at_roulette[playerid]) return 1;

    roulette_chip_object[playerid] = CreateDynamicObject(1899,
        roulette_chip_positions[0][0],
        roulette_chip_positions[0][1],
        roulette_chip_positions[0][2] + 0.1,
        0.0, 0.0, 0.0,
        10, 0, playerid, 50.0);
    roulette_chip_position[playerid] = 0;
    roulette_chip_created[playerid] = true;
    return 1;
}
forward StopChatAnimTimer(playerid);
public StopChatAnimTimer(playerid)
{
    if(is_chatting[playerid])
    {
        ClearAnimations(playerid, 1);
        is_chatting[playerid] = false;
    }
    return 1;
}

forward ResetPayLimit(playerid);
public ResetPayLimit(playerid)
{
    pay_count[playerid] = 0;
    pay_limit_timer[playerid] = 0;
    return 1;
}
forward EnableControl(playerid);
public EnableControl(playerid)
{
    TogglePlayerControllable(playerid, 1);
    ClearAnimations(playerid, 1);
    return 1;
}
forward RouletteCreationDone(playerid);
public RouletteCreationDone(playerid)
{
    roulette_creating[playerid] = false;
    return 1;
}
forward StopPayAnim(playerid, targetid);
public StopPayAnim(playerid, targetid)
{
    ClearAnimations(playerid, 1);
    ClearAnimations(targetid, 1);
    return 1;
}
forward SpinNumberDisplay();
public SpinNumberDisplay()
{
    roulette_number_index++;
    if(roulette_number_index >= sizeof(roulette_wheel_numbers))
        roulette_number_index = 0;

    new number = roulette_wheel_numbers[roulette_number_index];
    new outline_color;
    new color = GetNumberColor(number, outline_color);

    new str[8];
    format(str, sizeof(str), "%d", number);
    TextDrawSetString(roulette_number_td, str);
    TextDrawColor(roulette_number_td, color);
    TextDrawBackgroundColor(roulette_number_td, outline_color);
    TextDrawShowForAll(roulette_number_td);

    return 1;
}
// ==================== BCRYPT ÊÎËÁÝÊÈ ====================

forward OnPasswordHashed(playerid, hashid);
public OnPasswordHashed(playerid, hashid)
{
    bcrypt_get_hash(player_info[playerid][pass], BCRYPT_HASH_LENGTH);

    SPD(playerid, DLG_REG_GENDER, DIALOG_STYLE_MSGBOX, "{FF9900}Ðåãèñòðàöèÿ", "{FFFFFF}- ×òî-òî ÿ íå ïîéìó, òû ìóæ÷èíà èëè æåíùèíà? Âûãëÿäèøü êàê ëåñáèÿíêà.\n- Âûáåðè ïîë äëÿ ñâîåãî ïåðñîíàæà, ÷òîáû äðóãèå ãðàæäàíå íå ïóòàëèñü êàê ÿ.", "ß ìóæ÷èíà", "ß æåíùèíà");
    return 1;
}

forward OnPasswordChecked(playerid, bool:success);
public OnPasswordChecked(playerid, bool:success)
{
    if(success)
    {
        login_attempts[playerid] = 0;
        is_logged[playerid] = true;
        in_skin_select[playerid] = false;

        mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `accounts` WHERE `name` = '%e'", player_info[playerid][name]);
        mysql_tquery(dbHandle, query, "OnPlayerDataLoaded", "i", playerid);

        SCM(playerid, COLOR_GREEN, "{FF9900}Ñ âîçâðàùåíèåì â Êàëèôîðíèþ!");
    }
    else
    {
        login_attempts[playerid]++;

        if(login_attempts[playerid] >= 3)
        {
            SCM(playerid, COLOR_LIGHTRED, "- Âû ââåëè íåâåðíûé ïàðîëü 3 ðàçà. Âû êèêíóòû.");
            return Kick(playerid);
        }

        new attempts_left = 3 - login_attempts[playerid];
        new str[256];
        format(str, sizeof(str), "{FFFFFF}- Íåâåðíûé ïàðîëü! Îñòàëîñü ïîïûòîê: %d\n- Òû çàðåãèñòðèðîâàí, ââåäè ñâîé ïàðîëü.\n\nÒâî¸ èìÿ: %s[%i]", attempts_left, player_info[playerid][name], playerid);
        SPD(playerid, DLG_LOGIN, DIALOG_STYLE_PASSWORD, "{FF9900}Àâòîðèçàöèÿ", str, "Âîéòè", "Îòìåíà");
    }
    return 1;
}
public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid) {
    // Êîä ðóëåòêè
    if(at_roulette[playerid])
    {
        if(playertextid == roulette_exit_td[playerid])
        {
            Roul_DestroyTD(playerid);
            at_roulette[playerid] = false;
            return 1;
        }

        if(playertextid == casinoo_PTD[playerid][0])
        {
            new cur = roulette_chip_position[playerid];
            new newpos = cur;

            if(cur == 0) newpos = 2;
            else if(cur == 1) newpos = 4; else if(cur == 2) newpos = 5; else if(cur == 3) newpos = 6;
            else if(cur == 4) newpos = 7; else if(cur == 5) newpos = 8; else if(cur == 6) newpos = 9;
            else if(cur == 7) newpos = 10; else if(cur == 8) newpos = 11; else if(cur == 9) newpos = 12;
            else if(cur == 10) newpos = 13; else if(cur == 11) newpos = 14; else if(cur == 12) newpos = 15;
            else if(cur == 13) newpos = 16; else if(cur == 14) newpos = 17; else if(cur == 15) newpos = 18;
            else if(cur == 16) newpos = 19; else if(cur == 17) newpos = 20; else if(cur == 18) newpos = 21;
            else if(cur == 19) newpos = 22; else if(cur == 20) newpos = 23; else if(cur == 21) newpos = 24;
            else if(cur == 22) newpos = 25; else if(cur == 23) newpos = 26; else if(cur == 24) newpos = 27;
            else if(cur == 25) newpos = 28; else if(cur == 26) newpos = 29; else if(cur == 27) newpos = 30;
            else if(cur == 28) newpos = 31; else if(cur == 29) newpos = 32; else if(cur == 30) newpos = 33;
            else if(cur == 31) newpos = 34; else if(cur == 32) newpos = 35; else if(cur == 33) newpos = 36;
            else if(cur == 34) newpos = 37; else if(cur == 35) newpos = 38; else if(cur == 36) newpos = 39;
            else if(cur == 37) newpos = 0; else if(cur == 38) newpos = 0; else if(cur == 39) newpos = 0;
            else if(cur == 40) newpos = 41; else if(cur == 41) newpos = 42; else if(cur == 42) newpos = 40;
            else if(cur == 43) newpos = 44; else if(cur == 44) newpos = 45; else if(cur == 45) newpos = 46;
            else if(cur == 46) newpos = 47; else if(cur == 47) newpos = 48; else if(cur == 48) newpos = 43;

            MoveRouletteChip(playerid, newpos);
            return 1;
        }

        if(playertextid == casinoo_PTD[playerid][1])
        {
            new cur = roulette_chip_position[playerid];
            new newpos = cur;

            if(cur == 0) newpos = 38;
            else if(cur == 1) newpos = 0; else if(cur == 2) newpos = 0; else if(cur == 3) newpos = 0;
            else if(cur == 4) newpos = 1; else if(cur == 5) newpos = 2; else if(cur == 6) newpos = 3;
            else if(cur == 7) newpos = 4; else if(cur == 8) newpos = 5; else if(cur == 9) newpos = 6;
            else if(cur == 10) newpos = 7; else if(cur == 11) newpos = 8; else if(cur == 12) newpos = 9;
            else if(cur == 13) newpos = 10; else if(cur == 14) newpos = 11; else if(cur == 15) newpos = 12;
            else if(cur == 16) newpos = 13; else if(cur == 17) newpos = 14; else if(cur == 18) newpos = 15;
            else if(cur == 19) newpos = 16; else if(cur == 20) newpos = 17; else if(cur == 21) newpos = 18;
            else if(cur == 22) newpos = 19; else if(cur == 23) newpos = 20; else if(cur == 24) newpos = 21;
            else if(cur == 25) newpos = 22; else if(cur == 26) newpos = 23; else if(cur == 27) newpos = 24;
            else if(cur == 28) newpos = 25; else if(cur == 29) newpos = 26; else if(cur == 30) newpos = 27;
            else if(cur == 31) newpos = 28; else if(cur == 32) newpos = 29; else if(cur == 33) newpos = 30;
            else if(cur == 34) newpos = 31; else if(cur == 35) newpos = 32; else if(cur == 36) newpos = 33;
            else if(cur == 37) newpos = 34; else if(cur == 38) newpos = 35; else if(cur == 39) newpos = 36;
            else if(cur == 40) newpos = 42; else if(cur == 41) newpos = 40; else if(cur == 42) newpos = 41;
            else if(cur == 43) newpos = 48; else if(cur == 44) newpos = 43; else if(cur == 45) newpos = 44;
            else if(cur == 46) newpos = 45; else if(cur == 47) newpos = 46; else if(cur == 48) newpos = 47;

            MoveRouletteChip(playerid, newpos);
            return 1;
        }

        if(playertextid == casinoo_PTD[playerid][2])
        {
            new cur = roulette_chip_position[playerid];
            new newpos = cur;

            if(cur == 0) newpos = 0;
            else if(cur == 1) newpos = 2; else if(cur == 2) newpos = 3; else if(cur == 3) newpos = 43;
            else if(cur == 4) newpos = 5; else if(cur == 5) newpos = 6; else if(cur == 6) newpos = 43;
            else if(cur == 7) newpos = 8; else if(cur == 8) newpos = 9; else if(cur == 9) newpos = 44;
            else if(cur == 10) newpos = 11; else if(cur == 11) newpos = 12; else if(cur == 12) newpos = 44;
            else if(cur == 13) newpos = 14; else if(cur == 14) newpos = 15; else if(cur == 15) newpos = 45;
            else if(cur == 16) newpos = 17; else if(cur == 17) newpos = 18; else if(cur == 18) newpos = 45;
            else if(cur == 19) newpos = 20; else if(cur == 20) newpos = 21; else if(cur == 21) newpos = 46;
            else if(cur == 22) newpos = 23; else if(cur == 23) newpos = 24; else if(cur == 24) newpos = 46;
            else if(cur == 25) newpos = 26; else if(cur == 26) newpos = 27; else if(cur == 27) newpos = 47;
            else if(cur == 28) newpos = 29; else if(cur == 29) newpos = 30; else if(cur == 30) newpos = 47;
            else if(cur == 31) newpos = 32; else if(cur == 32) newpos = 33; else if(cur == 33) newpos = 48;
            else if(cur == 34) newpos = 35; else if(cur == 35) newpos = 36; else if(cur == 36) newpos = 48;
            else if(cur == 37) newpos = 38; else if(cur == 38) newpos = 39; else if(cur == 39) newpos = 37;
            else if(cur == 40) newpos = 1; else if(cur == 41) newpos = 13; else if(cur == 42) newpos = 25;
            else if(cur == 43) newpos = 40; else if(cur == 44) newpos = 40;
            else if(cur == 45) newpos = 41; else if(cur == 46) newpos = 41;
            else if(cur == 47) newpos = 42; else if(cur == 48) newpos = 42;

            MoveRouletteChip(playerid, newpos);
            return 1;
        }

        if(playertextid == casinoo_PTD[playerid][3])
        {
            new cur = roulette_chip_position[playerid];
            new newpos = cur;

            if(cur == 0) newpos = 0;
            else if(cur == 1) newpos = 40; else if(cur == 2) newpos = 1; else if(cur == 3) newpos = 2;
            else if(cur == 4) newpos = 40; else if(cur == 5) newpos = 4; else if(cur == 6) newpos = 5;
            else if(cur == 7) newpos = 40; else if(cur == 8) newpos = 7; else if(cur == 9) newpos = 8;
            else if(cur == 10) newpos = 40; else if(cur == 11) newpos = 10; else if(cur == 12) newpos = 11;
            else if(cur == 13) newpos = 41; else if(cur == 14) newpos = 13; else if(cur == 15) newpos = 14;
            else if(cur == 16) newpos = 41; else if(cur == 17) newpos = 16; else if(cur == 18) newpos = 17;
            else if(cur == 19) newpos = 41; else if(cur == 20) newpos = 19; else if(cur == 21) newpos = 20;
            else if(cur == 22) newpos = 41; else if(cur == 23) newpos = 22; else if(cur == 24) newpos = 23;
            else if(cur == 25) newpos = 42; else if(cur == 26) newpos = 25; else if(cur == 27) newpos = 26;
            else if(cur == 28) newpos = 42; else if(cur == 29) newpos = 28; else if(cur == 30) newpos = 29;
            else if(cur == 31) newpos = 42; else if(cur == 32) newpos = 31; else if(cur == 33) newpos = 32;
            else if(cur == 34) newpos = 42; else if(cur == 35) newpos = 34; else if(cur == 36) newpos = 35;
            else if(cur == 37) newpos = 39; else if(cur == 38) newpos = 37; else if(cur == 39) newpos = 38;
            else if(cur == 40) newpos = 43; else if(cur == 41) newpos = 45; else if(cur == 42) newpos = 47;
            else if(cur == 43) newpos = 3; else if(cur == 44) newpos = 9;
            else if(cur == 45) newpos = 15; else if(cur == 46) newpos = 21;
            else if(cur == 47) newpos = 27; else if(cur == 48) newpos = 33;

            MoveRouletteChip(playerid, newpos);
            return 1;
        }

        if(playertextid == casinoo_PTD[playerid][4])
        {
            new pos = roulette_chip_position[playerid];
            if(roulette_bet_placed[playerid])
                return SCM(playerid, COLOR_LIGHTRED, "[Ðóëåòêà] Âû óæå ñäåëàëè ñòàâêó!");
            if(roulette_spinning == 1)
                return SCM(playerid, COLOR_LIGHTRED, "[Ðóëåòêà] Èãðà óæå èä¸ò!");

            new str[128];
            format(str, sizeof(str), "{FFFFFF}Ââåäèòå ñóììó ñòàâêè:\nÎò {33AA33}100$ {FFFFFF}äî {33AA33}$1000$", pos);
            ShowPlayerDialog(playerid, 4001, DIALOG_STYLE_INPUT, "{FF9900}Ðóëåòêà - Ñòàâêà", str, "Ïîñòàâèòü", "Îòìåíà");
            return 1;
        }
        return 1;
    }

    // Âûáîð ñêèíà ïðè ðåãèñòðàöèè
    if(in_skin_select[playerid])
    {
        new skins_count;
        if(player_info[playerid][gender] == 1)
            skins_count = sizeof(male_skins);
        else
            skins_count = sizeof(female_skins);

        if(playertextid == btn_left[playerid])
        {
            player_skin_index[playerid]--;
            if(player_skin_index[playerid] < 0)
                player_skin_index[playerid] = skins_count - 1;

            new skinid;
            if(player_info[playerid][gender] == 1)
                skinid = male_skins[player_skin_index[playerid]];
            else
                skinid = female_skins[player_skin_index[playerid]];

            SetPlayerSkin(playerid, skinid);
            return 1;
        }

        if(playertextid == btn_right[playerid])
        {
            player_skin_index[playerid]++;
            if(player_skin_index[playerid] >= skins_count)
                player_skin_index[playerid] = 0;

            new skinid;
            if(player_info[playerid][gender] == 1)
                skinid = male_skins[player_skin_index[playerid]];
            else
                skinid = female_skins[player_skin_index[playerid]];

            SetPlayerSkin(playerid, skinid);
            return 1;
        }

        if(playertextid == btn_select[playerid])
        {
            new skinid;
            if(player_info[playerid][gender] == 1)
                skinid = male_skins[player_skin_index[playerid]];
            else
                skinid = female_skins[player_skin_index[playerid]];

            player_info[playerid][skin] = skinid;
            is_logged[playerid] = true;

            ClearSkinSelection(playerid);

            SetPlayerSkin(playerid, skinid);
            SpawnPlayer(playerid);

            new save_query[1024];
            mysql_format(dbHandle, save_query, sizeof(save_query),
                "INSERT INTO `accounts` (`name`, `password`, `gender`, `skin`, `admin`, `money`, `level`, `exp`, `passport_id`, `driver_license`) VALUES ('%e', '%e', %d, %d, %d, %d, %d, %d, %d, %d)",
                player_info[playerid][name], player_info[playerid][pass],
                player_info[playerid][gender], player_info[playerid][skin],
                player_info[playerid][admin_level], player_info[playerid][money],
                player_info[playerid][pLevel], player_info[playerid][pExp],
                player_info[playerid][pPassportID], player_info[playerid][pDriverLicense]);
            mysql_tquery(dbHandle, save_query, "OnPlayerDataSaved", "i", playerid);

            SCM(playerid, COLOR_GREEN, "{FF9900}Ðåãèñòðàöèÿ óñïåøíà! Äîáðî ïîæàëîâàòü â Êàëèôîðíèþ!");
            return 1;
        }
    }
    return 1;
}
//=============================================
// ÊÎÌÀÍÄÛ
//=============================================
CMD:makeadmin(playerid, params[])
{
    if(player_info[playerid][admin_level] < 5) return 0;

    new targetid, level;
    if(sscanf(params, "ui", targetid, level))
        return SCM(playerid, COLOR_WHITE, "/makeadmin [id] [óðîâåíü 1-5]");

    if(!IsPlayerConnected(targetid))
        return SCM(playerid, COLOR_LIGHTRED, "- Èãðîê íå íàéäåí!");

    if(level < 1 || level > 5)
        return SCM(playerid, COLOR_LIGHTRED, "- Óðîâåíü äîëæåí áûòü îò 1 äî 5!");

    player_info[targetid][admin_level] = level;
    SavePlayerData(targetid);

    new msg[256];
    format(msg, sizeof(msg), "{FF9900}Âû âûäàëè %s àäìèíèñòðàòèâíûå ïðàâà óðîâíÿ %d!", player_info[targetid][name], level);
    SCM(playerid, COLOR_GREEN, msg);

    format(msg, sizeof(msg), "{FF9900}Âû ïîëó÷èëè àäìèíèñòðàòèâíûå ïðàâà óðîâíÿ %d!", level);
    SCM(targetid, COLOR_GREEN, msg);

    format(msg, sizeof(msg), "{FF9900}[Admin] %s âûäàë àäìèíêó %d óðîâíÿ èãðîêó %s",
           player_info[playerid][name], level, player_info[targetid][name]);
    SendAdminMessage(COLOR_GREEN, msg);
    return 1;
}

CMD:deladmin(playerid, params[])
{
    if(player_info[playerid][admin_level] < 5) return 0;

    new targetid;
    if(sscanf(params, "u", targetid))
        return SCM(playerid, COLOR_WHITE, "/deladmin [id]");

    if(!IsPlayerConnected(targetid))
        return SCM(playerid, COLOR_LIGHTRED, "- Èãðîê íå íàéäåí!");

    if(player_info[targetid][admin_level] == 0)
        return SCM(playerid, COLOR_LIGHTRED, "- Ó èãðîêà íåò àäìèíñêèõ ïðàâ!");

    player_info[targetid][admin_level] = 0;
    SavePlayerData(targetid);

    new msg[256];
    format(msg, sizeof(msg), "{FF9900}Âû ñíÿëè àäìèíèñòðàòèâíûå ïðàâà ñ %s!", player_info[targetid][name]);
    SCM(playerid, COLOR_GREEN, msg);

    format(msg, sizeof(msg), "{FF9900}Ñ âàñ ñíÿòû àäìèíèñòðàòèâíûå ïðàâà!");
    SCM(targetid, COLOR_GREEN, msg);

    format(msg, sizeof(msg), "{FF9900}[Admin] %s ñíÿë àäìèíêó ñ èãðîêà %s",
           player_info[playerid][name], player_info[targetid][name]);
    SendAdminMessage(COLOR_GREEN, msg);
    return 1;
}

CMD:goto(playerid, params[])
{
    if(player_info[playerid][admin_level] < 1) return 0;

    new targetid;
    if(sscanf(params, "u", targetid))
        return SCM(playerid, COLOR_WHITE, "/goto [id]");

    if(!IsPlayerConnected(targetid))
        return SCM(playerid, COLOR_LIGHTRED, "- Èãðîê íå íàéäåí!");

    new Float:x, Float:y, Float:z;
    GetPlayerPos(targetid, x, y, z);
    SetPlayerPos(playerid, x, y, z);

    new msg[128];
    format(msg, sizeof(msg), "{FF9900}Âû òåëåïîðòèðîâàëèñü ê èãðîêó %s[%d]", player_info[targetid][name], targetid);
    SCM(playerid, COLOR_GREEN, msg);

    format(msg, sizeof(msg), "{FF9900}[Admin] %s òåëåïîðòèðîâàëñÿ ê %s",
           player_info[playerid][name], player_info[targetid][name]);
    SendAdminMessage(COLOR_GREEN, msg);
    return 1;
}

CMD:bring(playerid, params[])
{
    if(player_info[playerid][admin_level] < 1) return 0;

    new targetid;
    if(sscanf(params, "u", targetid))
        return SCM(playerid, COLOR_WHITE, "/bring [id]");

    if(!IsPlayerConnected(targetid))
        return SCM(playerid, COLOR_LIGHTRED, "- Èãðîê íå íàéäåí!");

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    SetPlayerPos(targetid, x, y, z);

    new msg[128];
    format(msg, sizeof(msg), "{FF9900}Âû òåëåïîðòèðîâàëè èãðîêà %s[%d] ê ñåáå!", player_info[targetid][name], targetid);
    SCM(playerid, COLOR_GREEN, msg);

    format(msg, sizeof(msg), "{FF9900}Àäìèíèñòðàòîð òåëåïîðòèðîâàë âàñ ê ñåáå");
    SCM(targetid, COLOR_GREEN, msg);

    format(msg, sizeof(msg), "{FF9900}[Admin] %s òåëåïîðòèðîâàë ê ñåáå èãðîêà %s",
           player_info[playerid][name], player_info[targetid][name]);
    SendAdminMessage(COLOR_GREEN, msg);
    return 1;
}

CMD:kick(playerid, params[])
{
    if(player_info[playerid][admin_level] < 2) return 0;

    new targetid, reason[64];
    if(sscanf(params, "us[64]", targetid, reason))
        return SCM(playerid, COLOR_WHITE, "/kick [id] [ïðè÷èíà]");

    if(!IsPlayerConnected(targetid))
        return SCM(playerid, COLOR_LIGHTRED, "- Èãðîê íå íàéäåí!");

    new msg[256];
    format(msg, sizeof(msg), "{FF9900}Âû êèêíóëè èãðîêà %s. Ïðè÷èíà: %s", player_info[targetid][name], reason);
    SCM(playerid, COLOR_GREEN, msg);

    format(msg, sizeof(msg), "{FF9900}[Admin] %s êèêíóë èãðîêà %s. Ïðè÷èíà: %s",
           player_info[playerid][name], player_info[targetid][name], reason);
    SendAdminMessage(COLOR_GREEN, msg);

    SetTimerEx("KickPlayer", 500, false, "i", targetid);
    return 1;
}

CMD:admin(playerid)
{
    if(player_info[playerid][admin_level] == 0) return 0;

    new admin_names[][] = {"", "Ñòàæåð", "Ìîäåðàòîð", "Àäìèíèñòðàòîð", "Ãëàâíûé àäìèíèñòðàòîð", "Ñîçäàòåëü"};

    new msg[128];
    format(msg, sizeof(msg), "{FF9900}Âàø óðîâåíü àäìèíèñòðàòîðà: %s (LVL %d)",
           admin_names[player_info[playerid][admin_level]], player_info[playerid][admin_level]);
    SCM(playerid, COLOR_GREEN, msg);
    return 1;
}

CMD:a(playerid, params[])
{
    if(player_info[playerid][admin_level] < 1) return 0;

    new text[128];
    if(sscanf(params, "s[128]", text))
        return SCM(playerid, COLOR_WHITE, "/a [òåêñò]");

    new msg[160];
    format(msg, sizeof(msg), "{FF9900}[Admin Chat] %s [LVL %d]: %s",
           player_info[playerid][name], player_info[playerid][admin_level], text);
    SendAdminMessage(COLOR_GREEN, msg);
    return 1;
}

CMD:pay(playerid, params[])
{
    new targetid, amount;
    if(sscanf(params, "ui", targetid, amount))
        return SCM(playerid, COLOR_WHITE, "/pay [id] [ñóììà]");

    if(!IsPlayerConnected(targetid))
        return SCM(playerid, COLOR_LIGHTRED, "- Èãðîê íå íàéäåí!");

    if(targetid == playerid)
        return SCM(playerid, COLOR_LIGHTRED, "- Íåëüçÿ ïåðåäàòü äåíüãè ñàìîìó ñåáå!");

    new Float:px, Float:py, Float:pz;
	GetPlayerPos(targetid, px, py, pz);
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, px, py, pz))
        return SCM(playerid, COLOR_LIGHTRED, "- Âû ñëèøêîì äàëåêî îò èãðîêà!");

    if(amount <= 0 || amount > 5000)
        return SCM(playerid, COLOR_LIGHTRED, "- Ñóììà äîëæíà áûòü îò $1 äî $5,000!");

    new Float:current_time = GetTickCount();

    if(pay_limit_timer[playerid] == 1)
    {
        if((current_time - last_pay_time[playerid]) < 3000)
        {
            SCM(playerid, COLOR_LIGHTRED, "- Âû èñ÷åðïàëè ëèìèò ïåðåâîäîâ! Ïîäîæäèòå 3 ñåêóíäû.");
            return 0;
        }
        else
        {
            pay_count[playerid] = 0;
            pay_limit_timer[playerid] = 0;
        }
    }

    if(player_info[playerid][money] < amount)
        return SCM(playerid, COLOR_LIGHTRED, "- Ó âàñ íåäîñòàòî÷íî äåíåã!");

    pay_count[playerid]++;

    if(pay_count[playerid] >= 3)
    {
        pay_limit_timer[playerid] = 1;
        last_pay_time[playerid] = current_time;
        SCM(playerid, COLOR_LIGHTRED, "- Âû äîñòèãëè ëèìèòà ïåðåâîäîâ! Ñëåäóþùèé ïåðåâîä ÷åðåç 3 ñåêóíäû.");
    }

    player_info[playerid][money] -= amount;
    player_info[targetid][money] += amount;

    UpdatePlayerMoney(playerid);
    UpdatePlayerMoney(targetid);

    SavePlayerData(playerid);
    SavePlayerData(targetid);

    ApplyAnimation(playerid, "DEALER", "DEALER_DEAL", 4.1, 0, 0, 0, 0, 0, 1);
    ApplyAnimation(targetid, "DEALER", "DEALER_DEAL", 4.1, 0, 0, 0, 0, 0, 1);

    SetTimerEx("StopPayAnim", 3000, false, "ii", playerid, targetid);

    new msg[256];
    format(msg, sizeof(msg), "{FF9900}Âû ïåðåäàëè $%d èãðîêó %s[%d]", amount, player_info[targetid][name], targetid);
    SCM(playerid, COLOR_GREEN, msg);

    format(msg, sizeof(msg), "{FF9900}Èãðîê %s[%d] ïåðåäàë âàì $%d", player_info[playerid][name], playerid, amount);
    SCM(targetid, COLOR_GREEN, msg);

    if(pay_count[playerid] >= 3)
    {
        SetTimerEx("ResetPayLimit", 3000, false, "i", playerid);
    }

    return 1;
}

CMD:givemoney(playerid, params[])
{
    if(player_info[playerid][admin_level] < 5) return 0;

    new targetid, amount;
    if(sscanf(params, "ui", targetid, amount))
        return SCM(playerid, COLOR_WHITE, "/givemoney [id] [ñóììà]");

    if(!IsPlayerConnected(targetid))
        return SCM(playerid, COLOR_LIGHTRED, "- Èãðîê íå íàéäåí!");

    if(amount <= 0)
        return SCM(playerid, COLOR_LIGHTRED, "- Ñóììà äîëæíà áûòü áîëüøå 0!");

    player_info[targetid][money] += amount;
    UpdatePlayerMoney(targetid);
    SavePlayerData(targetid);

    new msg[256];
    format(msg, sizeof(msg), "{FF9900}Âû âûäàëè $%d èãðîêó %s[%d]", amount, player_info[targetid][name], targetid);
    SCM(playerid, COLOR_GREEN, msg);

    format(msg, sizeof(msg), "{FF9900}Àäìèíèñòðàòîð %s âûäàë âàì $%d", player_info[playerid][name], amount);
    SCM(targetid, COLOR_GREEN, msg);

    format(msg, sizeof(msg), "{FF9900}[Admin] %s âûäàë $%d èãðîêó %s",
           player_info[playerid][name], amount, player_info[targetid][name]);
    SendAdminMessage(COLOR_GREEN, msg);
    return 1;
}

CMD:me(playerid, params[])
{
    new text[128];
    if(sscanf(params, "s[128]", text))
        return SCM(playerid, COLOR_WHITE, "/me [äåéñòâèå]");

    new Float:current_time = GetTickCount();
    if((current_time - last_me_time[playerid]) < 3000)
    {
        SCM(playerid, COLOR_LIGHTRED, "- Íå ôëóäè! Ïîäîæäè 3 ñåêóíäû ïåðåä ñëåäóþùèì /me!");
        return 0;
    }
    last_me_time[playerid] = current_time;

    new msg[180];
    format(msg, sizeof(msg), "%s %s", player_info[playerid][name], text);

    new Float:me_x, Float:me_y, Float:me_z;
    GetPlayerPos(playerid, me_x, me_y, me_z);
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i) && IsPlayerInRangeOfPoint(i, 10.0, me_x, me_y, me_z))
        {
            SCM(i, 0xFF69B4AA, msg);
        }
    }

    if(chat_bubble[playerid] != Text3D:INVALID_3DTEXT_ID)
    {
        Delete3DTextLabel(chat_bubble[playerid]);
    }
    chat_bubble[playerid] = Create3DTextLabel(msg, 0xFF69B4FF, 0.0, 0.0, 0.0, 15.0, 0, 0);
    Attach3DTextLabelToPlayer(chat_bubble[playerid], playerid, 0.0, 0.0, 0.3);
    SetTimerEx("DeleteChatBubble", 5000, false, "ii", _:chat_bubble[playerid], playerid);

    return 1;
}

CMD:do(playerid, params[])
{
    new text[128];
    if(sscanf(params, "s[128]", text))
        return SCM(playerid, COLOR_WHITE, "/do [îïèñàíèå]");

    new Float:current_time = GetTickCount();
    if((current_time - last_do_time[playerid]) < 3000)
    {
        SCM(playerid, COLOR_LIGHTRED, "- Íå ôëóäè! Ïîäîæäè 3 ñåêóíäû ïåðåä ñëåäóþùèì /do!");
        return 0;
    }
    last_do_time[playerid] = current_time;

    new msg[180];
    format(msg, sizeof(msg), "%s (( %s ))", text, player_info[playerid][name]);

    new Float:do_x, Float:do_y, Float:do_z;
    GetPlayerPos(playerid, do_x, do_y, do_z);
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i) && IsPlayerInRangeOfPoint(i, 10.0, do_x, do_y, do_z))
        {
            SCM(i, 0xFF69B4AA, msg);
        }
    }

    if(chat_bubble[playerid] != Text3D:INVALID_3DTEXT_ID)
    {
        Delete3DTextLabel(chat_bubble[playerid]);
    }
    chat_bubble[playerid] = Create3DTextLabel(msg, 0xFF69B4FF, 0.0, 0.0, 0.0, 15.0, 0, 0);
    Attach3DTextLabelToPlayer(chat_bubble[playerid], playerid, 0.0, 0.0, 0.3);
    SetTimerEx("DeleteChatBubble", 5000, false, "ii", _:chat_bubble[playerid], playerid);

    return 1;
}

CMD:s(playerid, params[])
{
    new text[128];
    if(sscanf(params, "s[128]", text))
        return SCM(playerid, COLOR_WHITE, "/s [òåêñò]");

    new Float:current_time = GetTickCount();
    if((current_time - last_s_time[playerid]) < 3000)
    {
        SCM(playerid, COLOR_LIGHTRED, "- Íå ôëóäè! Ïîäîæäè 3 ñåêóíäû ïåðåä ñëåäóþùèì /s!");
        return 0;
    }
    last_s_time[playerid] = current_time;

    new msg[180];
    format(msg, sizeof(msg), "%s êðè÷èò: %s!", player_info[playerid][name], text);

    new Float:s_x, Float:s_y, Float:s_z;
    GetPlayerPos(playerid, s_x, s_y, s_z);
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i) && IsPlayerInRangeOfPoint(i, 30.0, s_x, s_y, s_z))
        {
            SCM(i, 0xFFFF00AA, msg);
        }
    }

    if(chat_bubble[playerid] != Text3D:INVALID_3DTEXT_ID)
    {
        Delete3DTextLabel(chat_bubble[playerid]);
    }
    chat_bubble[playerid] = Create3DTextLabel(msg, 0xFFFF00FF, 0.0, 0.0, 0.0, 30.0, 0, 0);
    Attach3DTextLabelToPlayer(chat_bubble[playerid], playerid, 0.0, 0.0, 0.3);
    SetTimerEx("DeleteChatBubble", 5000, false, "ii", _:chat_bubble[playerid], playerid);

    ApplyAnimation(playerid, "ON_LOOKERS", "shout_01", 4.1, 0, 0, 0, 0, 0, 1);
    is_chatting[playerid] = true;
    SetTimerEx("StopChatAnimTimer", 3000, false, "i", playerid);

    return 1;
}

CMD:n(playerid, params[])
{
    new text[128];
    if(sscanf(params, "s[128]", text))
        return SCM(playerid, COLOR_WHITE, "/n [òåêñò]");

    new Float:current_time = GetTickCount();
    if((current_time - last_n_time[playerid]) < 3000)
    {
        SCM(playerid, COLOR_LIGHTRED, "- Íå ôëóäè! Ïîäîæäè 3 ñåêóíäû ïåðåä ñëåäóþùèì /n!");
        return 0;
    }
    last_n_time[playerid] = current_time;

    new msg[180];
    format(msg, sizeof(msg), "(( %s: %s ))", player_info[playerid][name], text);

    new Float:n_x, Float:n_y, Float:n_z;
    GetPlayerPos(playerid, n_x, n_y, n_z);
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i) && IsPlayerInRangeOfPoint(i, 10.0, n_x, n_y, n_z))
        {
            SCM(i, 0xC0C0C0AA, msg);
        }
    }

    if(chat_bubble[playerid] != Text3D:INVALID_3DTEXT_ID)
    {
        Delete3DTextLabel(chat_bubble[playerid]);
    }
    chat_bubble[playerid] = Create3DTextLabel(msg, 0xC0C0C0FF, 0.0, 0.0, 0.0, 15.0, 0, 0);
    Attach3DTextLabelToPlayer(chat_bubble[playerid], playerid, 0.0, 0.0, 0.3);
    SetTimerEx("DeleteChatBubble", 5000, false, "ii", _:chat_bubble[playerid], playerid);

    return 1;
}
CMD:talk(playerid, params[])
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    new world = GetPlayerVirtualWorld(playerid);
    new str[512];

    if(world == 1 && GetPlayerDistanceFromPoint(playerid, 1955.8096, -1169.4681, 20.3881) < 3.0)
    {
        if(working_gardener[playerid])
        {
            format(str, sizeof(str), "{FFFFFF}- Ñïàñèáî çà ïîìîùü, âîò òâîè $%d çà ñîðâàííûå êóñòû!", weed_count[playerid]);
            ShowPlayerDialog(playerid, 1003, DIALOG_STYLE_MSGBOX, "{FF9900}Ñàäîâíèê Äæåê", str, "Îê", "");
            return 1;
        }

        format(str, sizeof(str), "{FFFFFF}- Çäðàâñòâóé, íàì êàê ðàç íóæíû ëèøíèå ðóêè, íå õî÷åøü ïîìî÷ü?\n");
        ShowPlayerDialog(playerid, 1001, DIALOG_STYLE_MSGBOX, "{FF9900}Ñàäîâíèê Äæåê", str, "Äàëåå", "Îòêàçàòüñÿ");
        return 1;
    }

    if(world == 2 && GetPlayerDistanceFromPoint(playerid, 2441.2012, -1588.1819, 3009.0859) < 3.0)
    {
        if(player_info[playerid][pPassportID] != 0)
            return SCM(playerid, COLOR_LIGHTRED, "- Ó âàñ óæå åñòü ïàñïîðò!");

        if(passport_waiting[playerid])
            return SCM(playerid, COLOR_LIGHTRED, "- Âû óæå çàêàçàëè ïàñïîðò! Îæèäàéòå.");

        if(passport_ready[playerid])
		{
		    LastPassportID++;
		    player_info[playerid][pPassportID] = LastPassportID;
		    SavePlayerData(playerid);
		    passport_ready[playerid] = false;

		    format(str, sizeof(str), "{FFFFFF}- Âîò âàø ïàñïîðò, õîðîøåãî äíÿ!\n\n{FF9900}Íîìåð ïàñïîðòà: #%d",
		           player_info[playerid][pPassportID]);
		    ShowPlayerDialog(playerid, 2005, DIALOG_STYLE_MSGBOX, "{FF9900}Ïàñïîðòèñòêà", str, "Ñïàñèáî", "");
		    SCM(playerid, COLOR_GREEN, "{FF6347}[Ïîäñêàçêà]{FFFFFF} Èñïîëüçóéòå /pass.");
		    return 1;
		}

        format(str, sizeof(str), "{FFFFFF}- ×òîáû ïîëó÷èòü ïàñïîðò, çàïëàòèòå ïîøëèíó â ðàçìåðå $3.");
        ShowPlayerDialog(playerid, 2003, DIALOG_STYLE_MSGBOX, "{FF9900}Ïàñïîðòèñòêà", str, "Äàëåå", "Îòêàçàòüñÿ");
        return 1;
    }

	if(world == 3 && GetPlayerDistanceFromPoint(playerid, 1196.3639, -1804.8857, 3001.0859) < 3.0)
	{
	    if(has_driver_license[playerid])
	        return SCM(playerid, COLOR_LIGHTRED, "- Ó âàñ óæå åñòü âîäèòåëüñêèå ïðàâà!");

	    if(exam_practice_passed[playerid])
	    {
	        has_driver_license[playerid] = true;
	        player_info[playerid][pDriverLicense] = 1;
	        SavePlayerData(playerid);
	        exam_practice_passed[playerid] = false;

	        format(str, sizeof(str), "{FFFFFF}- Ïîçäðàâëÿþ, âîò âàøå âîäèòåëüñêîå óäîñòîâåðåíèå!\n\n{FF9900}Òåïåðü âû ìîæåòå óïðàâëÿòü àâòîìîáèëåì.");
	        ShowPlayerDialog(playerid, 3200, DIALOG_STYLE_MSGBOX, "{FF9900}Èíñòðóêòîð", str, "Ñïàñèáî", "");
	        SCM(playerid, COLOR_GREEN, "{FF9900}[Ïðàâà] Âû ïîëó÷èëè âîäèòåëüñêîå óäîñòîâåðåíèå!");
	        return 1;
	    }

	    if(exam_theory_passed[playerid])
	    {
	        if(exam_practice_started[playerid])
	        {
	            format(str, sizeof(str), "{FFFFFF}- Âû óæå íà÷àëè ïðàêòè÷åñêèé ýêçàìåí!\n\nÑàäèòåñü â ëþáóþ áåëóþ ìàøèíó ó çäàíèÿ àâòîøêîëû.");
	            ShowPlayerDialog(playerid, 3099, DIALOG_STYLE_MSGBOX, "{FF9900}Èíñòðóêòîð", str, "Îê", "");
	            return 1;
	        }

	        format(str, sizeof(str), "{FFFFFF}- Îòëè÷íî! Òåïåðü ïðàêòè÷åñêàÿ ÷àñòü.\n\nÂàì íóæíî ïðîåõàòü ïî ìàðøðóòó.\n{FF9900}Íà÷í¸ì ýêçàìåí?");
	        ShowPlayerDialog(playerid, 3100, DIALOG_STYLE_MSGBOX, "{FF9900}Èíñòðóêòîð", str, "Íà÷àòü", "Îòìåíà");
	        return 1;
	    }

	    format(str, sizeof(str), "{FFFFFF}- Çäðàâñòâóéòå! Âû ïðèøëè ñäàòü ýêçàìåí íà âîæäåíèå?");
	    ShowPlayerDialog(playerid, 3001, DIALOG_STYLE_MSGBOX, "{FF9900}Èíñòðóêòîð", str, "Äà", "Íåò");
	    return 1;
	}

	if(world == 1 && GetPlayerDistanceFromPoint(playerid, 1757.4216, -1682.4900, 13.4919) < 2.0)
	{
	    if(bike_rented[playerid])
	    {
	        if(GetVehicleModel(rented_bike_id[playerid]) != 0)
	            return SCM(playerid, COLOR_LIGHTRED, "[Àðåíäà] Âû óæå àðåíäîâàëè âåëîñèïåä!");
	        else
	            bike_rented[playerid] = false;
	    }
	    if(player_info[playerid][pLevel] < 3)
	    {
	        format(str, sizeof(str), "{FFFFFF}- Çäðàâñòâóéòå, âû õîòèòå àðåíäîâàòü âåëîñèïåä? Äëÿ âàñ àðåíäà âåëîñèïåäà áåñïëàòíî!");
	    }
	    else
	    {
	        format(str, sizeof(str), "{FFFFFF}- Çäðàâñòâóéòå, âû õîòèòå àðåíäîâàòü âåëîñèïåä? Äëÿ âàñ àðåíäà âåëîñèïåäà ñòîèò $3.");
	    }
	    ShowPlayerDialog(playerid, 6001, DIALOG_STYLE_MSGBOX, "{FF9900}Àðåíäà âåëîñèïåäîâ", str, "Îê", "Îòìåíà");
	    return 1;
	}
	if(world == 1 && GetPlayerDistanceFromPoint(playerid, 1761.9163, -1684.6316, 13.3984) < 3.0)
	{
	    if(player_info[playerid][pLevel] < 3)
	    {
	        format(str, sizeof(str), "{FFFFFF}- Çäðàâèÿ, ïåðåêóñèòü æåëàåòå? Äëÿ âàñ êîìïëåêñíûé îáåä çà ìîé ñ÷¸ò.");
	        ShowPlayerDialog(playerid, 7001, DIALOG_STYLE_MSGBOX, "{FF9900}Ïðîäàâåö õîò-äîãîâ", str, "Äà, õî÷ó", "Íåò, ñïàñèáî");
	    }
	    else
	    {
	        format(str, sizeof(str), "{FFFFFF}- Çäðàâèÿ, ïåðåêóñèòü æåëàåòå? Äëÿ âàñ êîìïëåêñíûé îáåä 5$.");
	        ShowPlayerDialog(playerid, 7001, DIALOG_STYLE_MSGBOX, "{FF9900}Ïðîäàâåö õîò-äîãîâ", str, "Äà, õî÷ó", "Íåò, ñïàñèáî");
	    }
	    return 1;
	}
    return SCM(playerid, COLOR_LIGHTRED, "- Ðÿäîì ñ âàìè íåò NPC!");
}
CMD:tpc(playerid, params[])
{
    if(player_info[playerid][admin_level] < 2)
        return 0;

    new Float:x, Float:y, Float:z, world;
    if(sscanf(params, "fffi", x, y, z, world))
        return SCM(playerid, COLOR_WHITE, "/tpc [x] [y] [z] [âèðòóàëüíûé ìèð]");

    if(world < 0 || world > 10000)
        return SCM(playerid, COLOR_LIGHTRED, "- Âèðòóàëüíûé ìèð äîëæåí áûòü îò 0 äî 10000!");

    SetPlayerPos(playerid, x, y, z);
    SetPlayerVirtualWorld(playerid, world);
    SetPlayerInterior(playerid, 0);

    new msg[160];
    format(msg, sizeof(msg), "{FF9900}Âû òåëåïîðòèðîâàëèñü: X: %.2f Y: %.2f Z: %.2f VW: %d", x, y, z, world);
    SCM(playerid, COLOR_GREEN, msg);

    format(msg, sizeof(msg), "{FF9900}[Admin] %s òåëåïîðòèðîâàëñÿ íà X: %.2f Y: %.2f Z: %.2f VW: %d",
           player_info[playerid][name], x, y, z, world);
    SendAdminMessage(COLOR_GREEN, msg);
    return 1;
}
CMD:pass(playerid, params[])
{
    new targetid;

    new Float:current_time = GetTickCount();
    if((current_time - last_pass_time[playerid]) < 3000)
    {
        SCM(playerid, COLOR_LIGHTRED, "- Íåëüçÿ ïîêàçûâàòü ïàñïîðò ÷àùå îäíîãî ðàçà â 3 ñåêóíäû!");
        return 0;
    }
    last_pass_time[playerid] = current_time;

    if(sscanf(params, "u", targetid))
    {
        targetid = playerid;
    }

    if(!IsPlayerConnected(targetid))
        return SCM(playerid, COLOR_LIGHTRED, "- Èãðîê íå íàéäåí!");

    if(player_info[playerid][pPassportID] == 0)
        return SCM(playerid, COLOR_LIGHTRED, "- Ó âàñ íåò ïàñïîðòà! Ïîëó÷èòå åãî â ïàñïîðòíîì ñòîëå.");

    new gender_str[8];
    if(player_info[playerid][gender] == 1)
        gender_str = "Ìóæñêîé";
    else
        gender_str = "Æåíñêèé";

    new str[512];
    format(str, sizeof(str),
        "{FFFFFF}Èìÿ ãðàæäàíèíà: {FF9900}%s\n\n\
        {FFFFFF}Ëåò â øòàòå: {FF9900}%d\n\n\
        {FFFFFF}Ïîë: {FF9900}%s\n\n\
        {FFFFFF}Íîìåð ïàñïîðòà: {FF9900}#%d",
        player_info[playerid][name],
        player_info[playerid][pLevel],
        gender_str,
        player_info[playerid][pPassportID]
    );

    if(targetid == playerid)
    {
        ShowPlayerDialog(playerid, 2001, DIALOG_STYLE_MSGBOX, "{FF9900}Âàø ïàñïîðò", str, "Çàêðûòü", "");
    }
    else
    {
        new title[64];
        format(title, sizeof(title), "{FF9900}Ïàñïîðò %s", player_info[playerid][name]);
        ShowPlayerDialog(targetid, 2001, DIALOG_STYLE_MSGBOX, title, str, "Çàêðûòü", "");
        SCM(playerid, COLOR_GREEN, "{FF9900}Âû ïîêàçàëè ñâîé ïàñïîðò!");
    }
    return 1;
}
CMD:engine(playerid, params[])
{
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        new model = GetVehicleModel(vehicleid);

        if(model == 510 || model == 481 || model == 509)
            return 1;

        new engine, lights, alarm, doors, bonnet, boot, objective;
        GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

        if(engine == 0)
        {
            SetVehicleParamsEx(vehicleid, 1, lights, alarm, doors, bonnet, boot, objective);
            PlayerPlaySound(playerid, 1138, 0.0, 0.0, 0.0);
            SCM(playerid, COLOR_GREEN, "{33AA33}[Äâèãàòåëü] Çàâåä¸í");
        }
        else
        {
            SetVehicleParamsEx(vehicleid, 0, lights, alarm, doors, bonnet, boot, objective);
            PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
            SCM(playerid, COLOR_GREEN, "{FF6347}[Äâèãàòåëü] Çàãëóøåí");
        }
    }
    return 1;
}
CMD:sethealth(playerid, params[])
{
    if(player_info[playerid][admin_level] < 3) return 0;

    new targetid, Float:health;
    if(sscanf(params, "uf", targetid, health))
        return SCM(playerid, COLOR_WHITE, "/sethealth [id] [0.0-100.0]");

    if(!IsPlayerConnected(targetid))
        return SCM(playerid, COLOR_LIGHTRED, "- Èãðîê íå íàéäåí!");

    if(health < 0.0 || health > 100.0)
        return SCM(playerid, COLOR_LIGHTRED, "- Çäîðîâüå äîëæíî áûòü îò 0.0 äî 100.0!");

    SetPlayerHealth(targetid, health);
    player_info[targetid][pHealth] = health; // Ñîõðàíÿåì â ïåðåìåííóþ
    SavePlayerData(targetid); // Ñîõðàíÿåì â ÁÄ

    new msg[128];
    format(msg, sizeof(msg), "{FF9900}Âû óñòàíîâèëè çäîðîâüå %.1f èãðîêó %s", health, player_info[targetid][name]);
    SCM(playerid, COLOR_GREEN, msg);
    return 1;
}
CMD:setskin(playerid, params[])
{
    if(player_info[playerid][admin_level] < 2) return 0;

    new targetid, skinid;
    if(sscanf(params, "ui", targetid, skinid))
        return SCM(playerid, COLOR_WHITE, "/setskin [id] [skin id]");

    if(!IsPlayerConnected(targetid))
        return SCM(playerid, COLOR_LIGHTRED, "- Èãðîê íå íàéäåí!");

    if(skinid < 0 || skinid > 311)
        return SCM(playerid, COLOR_LIGHTRED, "- Íåâåðíûé ID ñêèíà! Äîïóñòèìûå çíà÷åíèÿ: 0-311");

    // Óñòàíàâëèâàåì ñêèí
    SetPlayerSkin(targetid, skinid);

    new msg[256];
    format(msg, sizeof(msg), "{FF9900}Âû èçìåíèëè ñêèí èãðîêà %s[%d] íà ID: %d", player_info[targetid][name], targetid, skinid);
    SCM(playerid, COLOR_GREEN, msg);

    format(msg, sizeof(msg), "{FF9900}Àäìèíèñòðàòîð %s èçìåíèë âàø ñêèí íà ID: %d", player_info[playerid][name], skinid);
    SCM(targetid, COLOR_GREEN, msg);

    format(msg, sizeof(msg), "{FF9900}[Admin] %s èçìåíèë ñêèí èãðîêó %s íà ID: %d",
           player_info[playerid][name], player_info[targetid][name], skinid);
    SendAdminMessage(COLOR_GREEN, msg);
    return 1;
}

CMD:skin(playerid, params[])
{
    if(player_info[playerid][admin_level] < 2) return 0;

    new skinid;
    if(sscanf(params, "i", skinid))
        return SCM(playerid, COLOR_WHITE, "/skin [skin id]");

    if(skinid < 0 || skinid > 311)
        return SCM(playerid, COLOR_LIGHTRED, "- Íåâåðíûé ID ñêèíà! Äîïóñòèìûå çíà÷åíèÿ: 0-311");

    // Óñòàíàâëèâàåì ñêèí ñåáå
    SetPlayerSkin(playerid, skinid);

    new msg[256];
    format(msg, sizeof(msg), "{FF9900}Âû èçìåíèëè ñâîé ñêèí íà ID: %d", skinid);
    SCM(playerid, COLOR_GREEN, msg);

    format(msg, sizeof(msg), "{FF9900}[Admin] %s èçìåíèë ñâîé ñêèí íà ID: %d",
           player_info[playerid][name], skinid);
    SendAdminMessage(COLOR_GREEN, msg);
    return 1;
}
