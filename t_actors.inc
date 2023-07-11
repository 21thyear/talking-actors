#if defined t_actors_included_
    #endinput
#endif

#define t_actors_included_
#define c_notification      0x23c552FF

new Iterator:TALKING_ACTORS_ID<27>,
    Iterator:ACTORS_ID<27>;
const MAX_ACTORS_MOOD = 4;
const ACTOR_MOOD_TYPE_GLAD = 0;
const ACTOR_MOOD_TYPE_FUNNY = 1;
const ACTOR_MOOD_TYPE_NEUTRAL = 2;
const ACTOR_MOOD_TYPE_ANGRY = 3;
const MAX_CHANCE = 100;
const Float:POINT_RANGE_DISTANCE = 2.5;

enum e_TALKING_ACTORS_COORDINATS
{
    tChar,
    Float: tPositionX,
    Float: tPositionY,
    Float: tPositionZ,
    Float: tAngle,
    tMood
};

enum e_TALKING_ACTORS_DIALOGS
{
    dNull = 0
};

static const m_actors_initialization[][e_TALKING_ACTORS_COORDINATS] =
{ 
    {1, 1827.7650, -1599.1841, 13.5402, 106.5718, 0},
    {2, 1874.8044, -1411.7909, 13.5703, 214.1981, 0},
    {3, 1626.4556, -1289.5414, 17.0234, 175.8345, 0},
    {4, 1439.3444, -1327.0747, 13.5496, 265.4613, 0},
    {5, 1464.6658, -1497.2328, 13.5469, 101.5536, 0},
    {6, 1405.4376, -1487.7448, 20.4394, 261.8220, 0},
    {7, 1403.8014, -1461.2872, 8.6719, 342.3912, 0},
    {8, 1367.1393, -1414.8463, 13.5500, 37.1624, 0},
    {9, 1301.2900, -1373.8269, 13.7235, 277.2824, 0},
    {10, 1189.2080, -1384.7701, 13.5356, 281.251, 0},
    {11, 1207.5636, -1422.8479, 13.3828, 95.0903, 0},
    {12, 1217.4994, -1501.0359, 10.0469, 344.6412, 0},
    {13, 1287.7378, -1504.9077, 10.0469, 266.1327, 0},
    {14, 1356.8092, -1487.3475, 13.5397, 69.2556, 0},
    {15, 1357.3835, -1573.9653, 13.5391, 172.3551, 0},
    {16, 1370.6876, -1715.2360, 8.8594, 352.5444, 0},
    {17, 1483.0225, -1701.7631, 14.0469, 202.5190, 0},
    {18, 1534.9658, -1754.7047, 13.5469, 316.8242, 0},
    {19, 1604.6603, -1674.8077, 13.5469, 241.6039, 0},
    {20, 1652.1487, -1565.1740, 13.5469, 270.7847, 0},
    {21, 1847.0844, -1758.6622, 13.5469, 13.9768, 0},
    {22, 1802.2579, -1602.4235, 13.5469, 165.2112, 0},
    {23, 1905.1367, -1923.2148, 13.5469, 187.9287, 0},
    {24, 1813.9923, -1725.8070, 13.5469, 204.9005, 0},
    {25, 1908.2153, -1764.8971, 13.5469, 267.6096, 0},
    {26, 1893.7655, -1791.9781, 13.5469, 176.3242, 0},
    {27, 1887.2544, -1941.4719, 13.5469, 344.2098, 0}
};

public OnGameModeInit()
{

    Actors_Initialization();

    #if defined tActors_OnGameModeInit
        return tActors_OnGameModeInit();
    #else
        return true;
    #endif
}
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif

#define OnGameModeInit tActors_OnGameModeInit
#if defined tActors_OnGameModeInit
    forward tActors_OnGameModeInit();
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    
    if(newkeys & KEY_NO)
    {
        foreach(new i : TALKING_ACTORS_ID) {
            if(IsPlayerInDynamicArea(playerid,i, true))
                return
                    CheckInfoProcces(playerid, i);
        }
       
    }

    #if defined tActors_OnPlayerKeyStateChange
        return tActors_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
    #else
        return true;
    #endif
}
#if defined _ALS_OnPlayerKeyStateChange
    #undef OnPlayerKeyStateChange
#else
    #define _ALS_OnPlayerKeyStateChange
#endif

#define OnPlayerKeyStateChange tActors_OnPlayerKeyStateChange
#if defined tActors_OnPlayerKeyStateChange
    forward tActors_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif


stock Actors_Initialization()
{

    for( new actors_count; actors_count < sizeof(m_actors_initialization); actors_count++ ) 
    {
        Iter_Add(ACTORS_ID, actors_count);
        Iter_Add(TALKING_ACTORS_ID, actors_count);

        new actor_mood = random(MAX_ACTORS_MOOD);
        m_actors_initialization[actors_count][tMood] = actor_mood;
    }

    foreach(new i : TALKING_ACTORS_ID)
    {
        i = CreateDynamicCircle(
            m_actors_initialization[i][tPositionX],
            m_actors_initialization[i][tPositionY],
            2.5
        );
    }

    foreach(new i : ACTORS_ID)
    {
        i = CreateDynamicActor(
            m_actors_initialization[i][tChar],
            m_actors_initialization[i][tPositionX],
            m_actors_initialization[i][tPositionY],
            m_actors_initialization[i][tPositionZ],
            m_actors_initialization[i][tAngle]
        );
    }

    return true;
}

stock CheckInfoProcces(playerid, actor_id)
{
    switch(m_actors_initialization[actor_id][tMood])
    {
        case ACTOR_MOOD_TYPE_GLAD:
        {
            return
                ShowGlad_Dialog(playerid);
        }
        case ACTOR_MOOD_TYPE_FUNNY:
        {
            return
                ShowFunny_Dialog(playerid);
        }
        case ACTOR_MOOD_TYPE_NEUTRAL:
        {
            return
                ShowNeutral_Dialog(playerid, actor_id);
        }
        case ACTOR_MOOD_TYPE_ANGRY:
        {
            return
                ShowAngry_Dialog(playerid, actor_id);
        }
    }
    return true;
}

stock ShowGlad_Dialog(playerid) {

    static const fmt_str[] = 
    "\
        Вы: У тебя сегодня какое-то очень светлое и радостное настроение, правда?\n\
        Что бы, на твой взгляд, могло быть причиной этому?\n\
        Человек: Да, действительно, я просто ощущаю, что все гладко складывается и жизнь наливает меня энергией.\n\
        Вы: Замечательно! Всегда приятно, когда в жизни находятся такие люди, которые могут нас вдохновлять и наполнять радостью.\
    ";
    new string[sizeof(fmt_str) + (-3 * 3) + 1];
    format(string, sizeof string, fmt_str, string);

    return
        ShowPlayerDialog(playerid, dNull, DIALOG_STYLE_MSGBOX, "Разговор с персонажем", string, "OK", "Закрыть");
}

stock ShowFunny_Dialog(playerid) {

    static const fmt_str[] = 
    "\
        Вы: Я рад(а), что вижу у тебя сегодня такое отличное настроение!\n\
        Не могёшь порассказать, что приводит тебя в такой приподнятой мнении?\n\
        Человек: Конечно! Сегодня я встретился(лась) со своими старыми друзьями,\n\
        и мы так хорошо провели время, что это просто не передать словами.\n\
        Вы: Отлично, когда наши любимые люди вдохновляют нас на новые свершения. Так держать!\
    ";
    new string[sizeof(fmt_str) + (-3 * 4) + 1];
    format(string, sizeof string, fmt_str, string);

    return
        ShowPlayerDialog(playerid, dNull, DIALOG_STYLE_MSGBOX, "Разговор с персонажем", string,
    "OK", "Закрыть");
}

stock ShowNeutral_Dialog(playerid, actor_id) {

    static const fmt_str[] = 
    "\
        Вы: Как дела? Что нового?\n\
        Человек: В целом, все в порядке. Новостей пока нет ничего особенного, но я рад(а) что ты спрашиваешь.\
    ";
    new string[sizeof(fmt_str) + (-5) + 1];
    format(string, sizeof string, fmt_str, string);

    SetActorInfo(playerid, actor_id);

    return
        ShowPlayerDialog(playerid, dNull, DIALOG_STYLE_MSGBOX, "Разговор с персонажем", string, "OK", "Закрыть");
}

stock ShowAngry_Dialog(playerid, actor_id) {

    static const fmt_str[] = 
    "\
        Вы: Может, сходим куда-нибудь, развлечемся? Я могу придумать что-нибудь интересное.\n\
        Человек: Не хочется никуда ходить и ничего делать.\n\
        Вы: Понимаю, но порой движение помогает выйти из уныния. Если захочешь, знаешь, что я готов помочь.\
    ";
    new string[sizeof(fmt_str) + (-3*2) + (-2)];
    format(string, sizeof string, fmt_str, string);

    SetActorInfo(playerid, actor_id);
    return
        ShowPlayerDialog(playerid, dNull, DIALOG_STYLE_MSGBOX, "Разговор с персонажем", string, "ОК", "Выход");
}

stock SetActorInfo(playerid, actor_id)
{
    switch(m_actors_initialization[actor_id][tMood])
    {
        case ACTOR_MOOD_TYPE_NEUTRAL..ACTOR_MOOD_TYPE_ANGRY:
        {
            SendClientMessage(playerid, c_notification, "Во время разговора вы заметили что персонаж не в настроении");
            SendClientMessage(playerid, c_notification, "Вы поговорили с персонажем, возможно его настроение изменилось");

            ChangeActorMood(actor_id);
        }
    }
}

stock ChangeActorMood(actor_id)
{
    switch(random(MAX_CHANCE))
    {
        case 0..35: return false;
        case 36..99:
            m_actors_initialization[actor_id][tMood] = ACTOR_MOOD_TYPE_FUNNY;
    }
    return true;
}
