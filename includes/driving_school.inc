/*
    ============================================
    DRIVING_SCHOOL.INC - АВТОШКОЛА
    ============================================
*/

/**
 * Инициализация автошколы
 */
InitializeDrivingSchool()
{
	// Создание автомобилей для экзамена
	for(new i = 0; i < 3; i++)
	{
		gExamCars[i] = CreateVehicle(445, 1297.8899 - (i * 3.0), -1866.3218, 13.5469, 0.0, 1, 1, 0);
		SetVehicleVirtualWorld(gExamCars[i], 1);
		ChangeVehicleColor(gExamCars[i], 1, 1);
		SetVehicleNumberPlate(gExamCars[i], "EXAM");
		SetVehicleParamsEx(gExamCars[i], 0, 0, 0, 0, 0, 0, 0);
		SetVehicleHealth(gExamCars[i], 1000.0);
		gVehicleEngine[gExamCars[i]] = false;
	}

	print("[OK] Автошкола инициализирована");
}

/**
 * Начало теоретического экзамена
 */
StartTheoryExam(playerid)
{
	if(gPlayerFlags[playerid] & PFLAG_EXAM_THEORY_PASSED)
	{
		SCM(playerid, COLOR_RED, "Вы ��же прошли теорию!");
		return 0;
	}

	// Здесь должен быть диалог с вопросами
	// Пока это placeholder
	gPlayerFlags[playerid] |= PFLAG_EXAM_THEORY_PASSED;
	gPlayerData[playerid][examErrors] = 0;

	SCM(playerid, COLOR_GREEN, "Вы начали теоретический экзамен!");

	return 1;
}

/**
 * Начало практического экзамена
 */
StartPracticalExam(playerid)
{
	if(!(gPlayerFlags[playerid] & PFLAG_EXAM_THEORY_PASSED))
	{
		SCM(playerid, COLOR_RED, "Сначала пройдите теоретический экзамен!");
		return 0;
	}

	if(gPlayerFlags[playerid] & PFLAG_EXAM_PRACTICE_STARTED)
	{
		SCM(playerid, COLOR_RED, "Вы уже на практическом экзамене!");
		return 0;
	}

	// Вход в автомобиль
	new car_id = -1;
	for(new i = 0; i < 3; i++)
	{
		if(!IsAnyoneInVehicle(gExamCars[i]))
		{
			car_id = gExamCars[i];
			break;
		}
	}

	if(car_id == -1)
	{
		SCM(playerid, COLOR_RED, "Нет свободных автомобилей!");
		return 0;
	}

	gPlayerFlags[playerid] |= PFLAG_EXAM_PRACTICE_STARTED;
	gPlayerData[playerid][examErrors] = 0;
	gPlayerData[playerid][examCheckpointIndex] = 0;
	gPlayerData[playerid][examPracticeTime] = GetTickCount();

	// Первый чекпоинт
	SetPlayerRaceCheckpoint(playerid, 0,
		gExamCheckpoints[0][0],
		gExamCheckpoints[0][1],
		gExamCheckpoints[0][2],
		0, 0, 0, 5.0);

	SCM(playerid, COLOR_GREEN, "Практический экзамен начался! Следуйте по маршруту!");

	return 1;
}

/**
 * Завершение экзамена с ошибкой
 */
FailExam(playerid, const reason[])
{
	gPlayerFlags[playerid] &= ~PFLAG_EXAM_PRACTICE_STARTED;
	gPlayerFlags[playerid] &= ~PFLAG_EXAM_PRACTICE_PASSED;
	gPlayerFlags[playerid] &= ~PFLAG_EXAM_THEORY_PASSED;
	gPlayerData[playerid][examCheckpointIndex] = 0;
	gPlayerData[playerid][examErrors] = 0;

	DisablePlayerRaceCheckpoint(playerid);

	new fail_message[128];
	format(fail_message, sizeof(fail_message), "Экзамен не пройден! Причина: %s", reason);
	SCM(playerid, COLOR_RED, fail_message);

	return 1;
}

/**
 * Проверка, есть ли кто-то в машине
 */
bool:IsAnyoneInVehicle(vehicleid)
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(!IsPlayerConnected(i)) continue;
		if(GetPlayerVehicleID(i) == vehicleid) return true;
	}
	return false;
}

/**
 * Проверка водительского удостоверения
 */
bool:HasDriverLicense(playerid)
{
	return (gPlayerFlags[playerid] & PFLAG_HAS_DRIVER_LICENSE) ? true : false;
}

/**
 * Выдача водительского удостоверения
 */
GiveDriverLicense(playerid)
{
	gPlayerFlags[playerid] |= PFLAG_HAS_DRIVER_LICENSE;
	gPlayerAccount[playerid][driver_license] = 1;
	SCM(playerid, COLOR_GREEN, "Вы получили водительское удостоверение!");
	return 1;
}

/**
 * Удаление водительского удостоверения
 */
RemoveDriverLicense(playerid)
{
	gPlayerFlags[playerid] &= ~PFLAG_HAS_DRIVER_LICENSE;
	gPlayerAccount[playerid][driver_license] = 0;
	SCM(playerid, COLOR_RED, "Ваше водительское удостоверение отозвано!");
	return 1;
}
