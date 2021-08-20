ProfBirch_EventScript_UpdateLocation:: @ 82720AD
	compare VAR_PETALBURG_GYM_STATE, 0
	goto_if_eq Common_EventScript_NopReturn
	goto_if_set FLAG_SYS_GAME_CLEAR, ProfBirch_EventScript_MoveToLab
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4
	goto_if_eq ProfBirch_EventScript_MoveToLab
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5
	goto_if_eq ProfBirch_EventScript_MoveToLab
	compare VAR_BIRCH_STATE, 0
	call_if_eq ProfBirch_EventScript_MoveToLab
	compare VAR_BIRCH_STATE, 1
	call_if_eq ProfBirch_EventScript_MoveToLab
	compare VAR_BIRCH_STATE, 2
	call_if_eq ProfBirch_EventScript_MoveToRoute101
	compare VAR_BIRCH_STATE, 3
	call_if_eq ProfBirch_EventScript_MoveToRoute101
	compare VAR_BIRCH_STATE, 4
	call_if_eq ProfBirch_EventScript_MoveToRoute103
	compare VAR_BIRCH_STATE, 5
	call_if_eq ProfBirch_EventScript_MoveToRoute103
	compare VAR_BIRCH_STATE, 6
	call_if_eq ProfBirch_EventScript_MoveToLab
	compare VAR_BIRCH_STATE, 7
	call_if_eq ProfBirch_EventScript_MoveToLab
	return

ProfBirch_EventScript_MoveToLab:: @ 827211A
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	setflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_ROUTE_103_BIRCH
	return

ProfBirch_EventScript_MoveToRoute101:: @ 8272127
	clearflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	setflag FLAG_HIDE_ROUTE_103_BIRCH
	return

ProfBirch_EventScript_MoveToRoute103:: @ 8272134
	clearflag FLAG_HIDE_ROUTE_103_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	return

ProfBirch_EventScript_RatePokedexOrRegister:: @ 8272141
	lock
	faceplayer
	goto_if_unset FLAG_HAS_MATCH_CALL, ProfBirch_EventScript_AskRatePokedex
	goto_if_unset FLAG_ENABLE_PROF_BIRCH_MATCH_CALL, EventScript_RegisterProfBirch

ProfBirch_EventScript_AskRatePokedex:: @ 8272155
	msgbox gBirchDexRatingText_AreYouCurious, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ProfBirch_EventScript_DeclineRating
	call ProfBirch_EventScript_RatePokedex
	call ProfBirch_EventScript_CheckLastHM
	release
	end

ProfBirch_EventScript_DeclineRating:: @ 827216F
	msgbox gBirchDexRatingText_Cancel, MSGBOX_DEFAULT
	release
	end

ProfBirch_EventScript_ShowRatingMessage:: @ 8272179
	copyvar VAR_0x8004, VAR_0x8009
	special ShowPokedexRatingMessage
	waitmessage
	waitbuttonpress
	return

ProfBirch_EventScript_RatePokedex:: @ 8272184
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring 0, VAR_0x8008  @ Num Hoenn seen
	buffernumberstring 1, VAR_0x8009  @ Num Hoenn caught
	msgbox gBirchDexRatingText_SoYouveSeenAndCaught, MSGBOX_DEFAULT
	call ProfBirch_EventScript_ShowRatingMessage
	compare VAR_0x800A, 0
	goto_if_eq Common_EventScript_NopReturn  @ National dex not enabled
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	buffernumberstring 0, VAR_0x8008  @ Num National seen
	buffernumberstring 1, VAR_0x8009  @ Num National caught
	msgbox gBirchDexRatingText_OnANationwideBasis, MSGBOX_DEFAULT
	return

ProfBirch_EventScript_PrepareBirchCall::
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1
	return

ProfBirch_EventScript_BirchCallCheckBadge::
	goto_if_set FLAG_BADGE01_GET, ProfBirch_EventScript_BirchCall
	goto_if_set FLAG_BADGE02_GET, ProfBirch_EventScript_BirchCall
	goto_if_set FLAG_BADGE03_GET, ProfBirch_EventScript_BirchCall
	end
	
ProfBirch_EventScript_BirchCall::
	call_if_set FLAG_ENABLE_PROF_BIRCH_MATCH_CALL, ProfBirch_EventScript_BirchCallRegistered
	call_if_unset FLAG_ENABLE_PROF_BIRCH_MATCH_CALL, ProfBirch_EventScript_BirchCallNotRegistered
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4
	end

ProfBirch_EventScript_BirchCallRegistered::
	lockall
	pokenavcall ProfBirch_Text_BirchFirstBadgeCallRegistered
	waitmessage
	releaseall
	return

ProfBirch_EventScript_BirchCallNotRegistered::
	lockall
	pokenavcall ProfBirch_Text_BirchFirstBadgeCallNotRegistered
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route110_Text_RegisteredBirchInPokenav, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
	releaseall
	return

ProfBirch_Text_BirchFirstBadgeCallRegistered:
	.string "PROF. BIRCH: Hey {PLAYER}!\n"
	.string "How are you?\p"
	.string "Is your POKéDEX doing well? Remember\n"
	.string "to search everywhere and catch\l"
	.string "every POKéMON you see.\p"
	.string "Oh, so you have challenged a GYM and\n"
	.string "obtained your first badge?\p"
	.string "You're just like your father NORMAN\n"
	.string "when he was your age.\p"
	.string "By the way, I have a present for you.\n"
	.string "Come by my lab when you can.\p"
	.string "I'll be waiting for you, {PLAYER}.\n"
	.string "Take care!$"

ProfBirch_Text_BirchFirstBadgeCallNotRegistered:
	.string "PROF. BIRCH: Hey {PLAYER}!\n"
	.string "How are you?\p"
	.string "MR. STONE told me that he had given\n"
	.string "you a POKéNAV, so I decided to\l"
	.string "tell you something.\p"
	.string "You can call me when you want,\n"
	.string "that way, even when we are apart\l"
	.string "I can rate your POKéDEX.\p"
	.string "Oh, so you have challenged a GYM and\n"
	.string "obtained your first badge?\p"
	.string "You're just like your father NORMAN\n"
	.string "when he was your age.\p"
	.string "By the way, I have a present for you.\n"
	.string "Come by my lab when you can.\p"
	.string "I'll be waiting for you, {PLAYER}.\n"
	.string "Take care!$"
	
ProfBirch_EventScript_CheckLastHM::
	call_if_unset ITEM_HM08, ProfBirch_EventScript_CheckIfCanGetHM
	return

ProfBirch_EventScript_CheckIfCanGetHM::
	specialvar VAR_0x8008, GetHMPokemonCount
	compare VAR_0x8009 ,VAR_0x8008
	call_if_ge ProfBirch_EventScript_LookForNextHM
	return

ProfBirch_EventScript_LookForNextHM::
	special SetNextHMToGet
	msgbox gProfBirch_Text_LookForAssistantHM, MSGBOX_DEFAULT
	return

gProfBirch_Text_LookForAssistantHM::
	.string "By the looks of your POKéDEX, you\n"
	.string "have caught enough POKéMON for\l"
	.string "me to give you {STR_VAR_3}.\p"
	.string "You have to look for one of my\n"
	.string "assistants. He'll give you it.$"

@ VAR_0x8009: HM to give
@ VAR_0x800A: Talking to 0-Scientist, 1-Prof.Cozmos

ScientistAssistant_EventScript_Main::
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4
	goto_if_eq ScientistAssistant_EventScript_ProfWaitingForYou
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5
	goto_if_eq ScientistAssistant_EventScript_ProfWaitingForYou
	special SetNextHMToGetAssistant
	compare VAR_0x800A, 1
	call_if_eq ScientistAssistant_EventScript_ProfCozmosCheckGreeting
	call_if_ne ScientistAssistant_EventScript_AssistantGreeting
	compare VAR_0x8004, 1
	goto_if_eq ScientistAssistant_EventScript_HaveEnoughPokemon
	goto ScientistAssistant_EventScript_DoNotHaveEnoughPokemon

ScientistAssistant_EventScript_ProfWaitingForYou::
	msgbox ScientistAssistant_Text_ProfWaitingForYou, MSGBOX_DEFAULT
	closemessage
	end

ScientistAssistant_EventScript_ProfCozmosCheckGreeting::
	call_if_unset FLAG_TALKED_HM04, ScientistAssistant_EventScript_ProfCozmosGreeting
	msgbox ScientistAssistant_Text_ProfCozmosDirectCheck, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_ProfCozmosGreeting::
	msgbox ScientistAssistant_Text_ProfCozmosFirstGreetPlayer, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_AssistantGreeting::
	msgbox ScientistAssistant_Text_AssistantDirectCheck, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_HaveEnoughPokemon::
	compare VAR_0x800A, 1
	call_if_eq ScientistAssistant_EventScript_ProfCozmosHaveEnoughPokeomMessage
	call_if_ne ScientistAssistant_EventScript_AssistantHaveEnoughPokemonMessage
	giveitem VAR_0x8009
	goto ScientistAssistant_EventScript_ExplainHM

ScientistAssistant_EventScript_ProfCozmosHaveEnoughPokeomMessage::
	msgbox ScientistAssistant_Text_ProfCozmosPerfectYouHavePokemonTakeHM, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_AssistantHaveEnoughPokemonMessage::
	msgbox ScientistAssistant_Text_AssistantPerfectYouHavePokemonTakeHM, MSGBOX_DEFAULT
	return	

ScientistAssistant_EventScript_DoNotHaveEnoughPokemon::
	msgbox ScientistAssistant_Text_SorryDontHaveEnoughPokemon, MSGBOX_DEFAULT
	closemessage
	releaseall
	end
	
ScientistAssistant_EventScript_ExplainHM::
	compare VAR_0x8009, ITEM_HM01
	call_if_eq ScientistAssistant_EventScript_AssistantGiveCut
	compare VAR_0x8009, ITEM_HM02
	call_if_eq ScientistAssistant_EventScript_AssistantGiveFly
	compare VAR_0x8009, ITEM_HM03
	call_if_eq ScientistAssistant_EventScript_ProfCozmosGiveStrength
	compare VAR_0x8009, ITEM_HM04
	call_if_eq ScientistAssistant_EventScript_AssistantGiveSurf
	compare VAR_0x8009, ITEM_HM05
	call_if_eq ScientistAssistant_EventScript_AssistantGiveFlash
	compare VAR_0x8009, ITEM_HM06
	call_if_eq ScientistAssistant_EventScript_AssistantGiveRockSmash
	compare VAR_0x8009, ITEM_HM07
	call_if_eq ScientistAssistant_EventScript_AssistantGiveWaterfall
	compare VAR_0x8009, ITEM_HM08
	call_if_eq ScientistAssistant_EventScript_AssistantGiveDive
	closemessage
	release
	end

ScientistAssistant_EventScript_AssistantGiveCut::
	setflag FLAG_RECEIVED_HM01
	msgbox ScientistAssistant_Text_AssistantExplainCut, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_AssistantGiveFly::
	setflag FLAG_RECEIVED_HM02
	msgbox ScientistAssistant_Text_AssistantExplainFly, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_AssistantGiveSurf::
	setflag FLAG_RECEIVED_HM03
	msgbox ScientistAssistant_Text_AssistantExplainSurf, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_ProfCozmosGiveStrength::
	setflag FLAG_RECEIVED_HM04
	msgbox ScientistAssistant_Text_ProfCozmosExplainStrength, MSGBOX_DEFAULT
	return
	
ScientistAssistant_EventScript_AssistantGiveFlash::
	setflag FLAG_RECEIVED_HM05
	msgbox ScientistAssistant_Text_AssistantExplainFlash, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_AssistantGiveRockSmash::
	setflag FLAG_RECEIVED_HM06
	msgbox ScientistAssistant_Text_AssistantExplainRockSmash, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_AssistantGiveWaterfall::
	setflag FLAG_RECEIVED_HM07
	msgbox ScientistAssistant_Text_AssistantExplainWaterfall, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_AssistantGiveDive::
	setflag FLAG_RECEIVED_HM08
	msgbox ScientistAssistant_Text_AssistantExplainDive, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_CutAssistantCheck::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM01, ScientistAssistant_EventScript_CutAssistantDialog
	call_if_unset FLAG_TALKED_HM01, ScientistAssistant_EventScript_CutFirstGreeting
	setvar VAR_0x8009, ITEM_HM01
	setvar VAR_0x800A, 0
	goto ScientistAssistant_EventScript_Main

ScientistAssistant_EventScript_CutFirstGreeting::
	setflag FLAG_TALKED_HM01
	msgbox ScientistAssistant_Text_AssistantPreCut, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_CutAssistantDialog::
	msgbox ScientistAssistant_Text_AssistantAfterGivingCut, MSGBOX_DEFAULT
	closemessage
	release
	end

ScientistAssistant_EventScript_FlyAssistantCheck::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM02, ScientistAssistant_EventScript_FlyAssistantDialog
	call_if_unset FLAG_TALKED_HM02, ScientistAssistant_EventScript_FlyFirstGreeting
	setvar VAR_0x8009, ITEM_HM02
	setvar VAR_0x800A, 0
	goto ScientistAssistant_EventScript_Main

ScientistAssistant_EventScript_FlyFirstGreeting::
	setflag FLAG_TALKED_HM02
	msgbox ScientistAssistant_Text_AssistantPreFly, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_FlyAssistantDialog::
	msgbox ScientistAssistant_Text_AssistantAfterGivingFly, MSGBOX_DEFAULT
	closemessage
	release
	end

ScientistAssistant_EventScript_SurfAssistantCheck::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM03, ScientistAssistant_EventScript_SurfAssistantDialog
	call_if_unset FLAG_TALKED_HM03, ScientistAssistant_EventScript_SurfFirstGreeting
	setvar VAR_0x8009, ITEM_HM03
	setvar VAR_0x800A, 0
	goto ScientistAssistant_EventScript_Main

ScientistAssistant_EventScript_SurfFirstGreeting::
	setflag FLAG_TALKED_HM03
	msgbox ScientistAssistant_Text_AssistantPreSurf, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_SurfAssistantDialog::
	msgbox ScientistAssistant_Text_AssistantAfterGivingSurf, MSGBOX_DEFAULT
	closemessage
	release
	end

ScientistAssistant_EventScript_FlashAssistantCheck::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM05, ScientistAssistant_EventScript_FlashAssistantDialog
	call_if_unset FLAG_TALKED_HM05, ScientistAssistant_EventScript_FlashFirstGreeting
	setvar VAR_0x8009, ITEM_HM05
	setvar VAR_0x800A, 0
	goto ScientistAssistant_EventScript_Main

ScientistAssistant_EventScript_FlashFirstGreeting::
	setflag FLAG_TALKED_HM05
	msgbox ScientistAssistant_Text_AssistantPreFlash, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_FlashAssistantDialog::
	msgbox ScientistAssistant_Text_AssistantAfterGivingFlash, MSGBOX_DEFAULT
	closemessage
	release
	end

ScientistAssistant_EventScript_RockSmashAssistantCheck::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM06, ScientistAssistant_EventScript_RockSmashAssistantDialog
	call_if_unset FLAG_TALKED_HM06, ScientistAssistant_EventScript_RockSmashFirstGreeting
	setvar VAR_0x8009, ITEM_HM06
	setvar VAR_0x800A, 0
	goto ScientistAssistant_EventScript_Main

ScientistAssistant_EventScript_RockSmashFirstGreeting::
	setflag FLAG_TALKED_HM06
	msgbox ScientistAssistant_Text_AssistantPreRockSmash, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_RockSmashAssistantDialog::
	msgbox ScientistAssistant_Text_AssistantAfterGivingRockSmash, MSGBOX_DEFAULT
	closemessage
	release
	end

ScientistAssistant_EventScript_WaterfallAssistantCheck::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM07, ScientistAssistant_EventScript_WaterfallAssistantDialog
	call_if_unset FLAG_TALKED_HM07, ScientistAssistant_EventScript_WaterfallFirstGreeting
	setvar VAR_0x8009, ITEM_HM07
	setvar VAR_0x800A, 0
	goto ScientistAssistant_EventScript_Main

ScientistAssistant_EventScript_WaterfallFirstGreeting::
	setflag FLAG_TALKED_HM07
	msgbox ScientistAssistant_Text_AssistantPreWaterfall, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_WaterfallAssistantDialog::
	msgbox ScientistAssistant_Text_AssistantAfterGivingWaterfall, MSGBOX_DEFAULT
	closemessage
	release
	end

ScientistAssistant_EventScript_DiveAssistantCheck::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM08, ScientistAssistant_EventScript_DiveAssistantDialog
	call_if_unset FLAG_TALKED_HM08, ScientistAssistant_EventScript_DiveFirstGreeting
	setvar VAR_0x8009, ITEM_HM08
	setvar VAR_0x800A, 0
	goto ScientistAssistant_EventScript_Main

ScientistAssistant_EventScript_DiveFirstGreeting::
	setflag FLAG_TALKED_HM08
	msgbox ScientistAssistant_Text_AssistantPreDive, MSGBOX_DEFAULT
	return

ScientistAssistant_EventScript_DiveAssistantDialog::
	msgbox ScientistAssistant_Text_AssistantAfterGivingDive, MSGBOX_DEFAULT
	closemessage
	release
	end

ScientistAssistant_Text_ProfWaitingForYou:
	.string "Haven't you gone to\n"
	.string "PROF. BIRCH's lab yet?\p"
	.string "He said he had something to give you.\n"
	.string "You should go and check.$"

ScientistAssistant_Text_ProfCozmosDirectCheck:
	.string "PROF. COZMOS: When you catch more than\n"
	.string "{STR_VAR_2} different POKéMON, then I'll\l"
	.string "give you {STR_VAR_3}.\p"
	.string "How is your POKéDEX doing?$"

ScientistAssistant_Text_AssistantDirectCheck:
	.string "I shall give you {STR_VAR_3} if you had\n"
	.string "caught at least {STR_VAR_2} different POKéMON.\p"
	.string "May I see how is your POKéDEX doing?$"

ScientistAssistant_Text_ProfCozmosPerfectYouHavePokemonTakeHM:
	.string "PROF. COZMOS: Perfect, you have\n"
	.string "enough POKéMON!\p"
	.string "Then I guess I should give you this.$"

ScientistAssistant_Text_AssistantPerfectYouHavePokemonTakeHM:
	.string "Good, you have caught enough POKéMON!\n"
	.string "Then I'll give you this HM, it's your\l"
	.string "reward for your hard work.$"

ScientistAssistant_Text_SorryDontHaveEnoughPokemon:
	.string "I'm sorry but it seems that you haven't\n"
	.string "caught enough POKéMON yet.$"

ScientistAssistant_Text_AssistantPreCut:
	.string "Did you know? There are items called\n"
	.string "HIDDEN MACHINES which can be used by\l"
	.string "POKéMON out of combat.\p"
	.string "They may break a rock or even allow\n"
	.string "you to ride them over water.\p"
	.string "By the way, you are {PLAYER}, right?\n"
	.string "I'm one of PROF. BIRCH assistants.$"

ScientistAssistant_Text_AssistantExplainCut:
	.string "That HIDDEN MACHINE, or HM for\n"
	.string "short, is CUT.\p"
	.string "An HM move is one that can be used\n"
	.string "by POKéMON outside of battle.\p"
	.string "The POKéMON does not need to know it,\n"
	.string "you just need a POKéMON who can learn\l"
	.string "it and have already earned the\l"
	.string "STONE BADGE from RUSTBORO's GYM.\p"
	.string "You'll be able to chop down thin trees\n"
	.string "when you find them in your way.$"

ScientistAssistant_Text_AssistantAfterGivingCut:
	.string "There are trees blocking ways\n"
	.string "everywhere.\p"
	.string "Now that you have CUT you know\n"
	.string "what you have to do.$"

ScientistAssistant_Text_AssistantPreFly:
	.string "Most of people use the ferry of\n"
	.string "SLATEPORT to move to LILYCOVE.\p"
	.string "But, wouldn't be great if you could\n"
	.string "travel to distant cities from\l"
	.string "any place in a blink?\p"
	.string "By the way, you are {PLAYER}, right?\n"
	.string "I'm one of PROF. BIRCH assistants.$"

ScientistAssistant_Text_AssistantExplainFly:
	.string "Use FLY and your POKéMON will instantly\n"
	.string "carry you to any town you've already\l"
	.string "visited.\p"
	.string "But, to use FLY, you have to get\n"
	.string "the GYM BADGE from FORTREE CITY.\l"
	.string "That's important, so don't forget.$"

ScientistAssistant_Text_AssistantAfterGivingFly:
	.string "It's amusing to be able to fly here and\n"
	.string "there whenever you want.\p"
	.string "It does not only allow you to save a lot\n"
	.string "of land traveling time, but also allows you\l"
	.string "to feel the cool breeze of the air.\l"
	.string "It's fascinating, don't you think?$"

ScientistAssistant_Text_AssistantPreSurf:
	.string "I saw a pass near the entrance which led\n"
	.string "to the east part of the SAFARI ZONE,\l"
	.string "but I wasn't allowed in.\p"
	.string "I wonder if there are any rare POKéMON\n"
	.string "there?\p"
	.string "By the way, you are {PLAYER}, right?\n"
	.string "I'm one of PROF. BIRCH assistants.$"

ScientistAssistant_Text_AssistantExplainSurf:
	.string "If you have any POKéMON that can\n"
	.string "learn SURF, you'll be able to\l"
	.string "ride it and visit all sort of places.\p"
	.string "A new world is now open to you, but\n"
	.string "only if you have PETALBURG's GYM BADGE.$"

ScientistAssistant_Text_AssistantAfterGivingSurf:
	.string "When it comes to exploring, the\n"
	.string "HIDDEN MACHINE SURF has no match.\p"
	.string "You can find hidden old places\n"
	.string "and visit lot of new ones.$"

ScientistAssistant_Text_ProfCozmosFirstGreetPlayer:
	.string "PROF. COZMOS: By the way, I'm friends\n"
	.string "with PROF. BIRCH and he told me to give\l"
	.string "you {STR_VAR_3} if you had already caught\l"
	.string "{STR_VAR_2} or more different POKéMON.\p"
	.string "How is your POKéDEX doing?$"

ScientistAssistant_Text_ProfCozmosExplainStrength:
	.string "PROF. COZMOS: That HM contains STRENGTH.\p"
	.string "If a muscular POKéMON were to learn\n"
	.string "that, it would be able to move even\l"
	.string "large boulders.\p"
	.string "Yet, to do that you need to have already\n"
	.string "the GYM BADGE from LAVARIDGE TOWN.$"

ScientistAssistant_Text_AssistantPreFlash:
	.string "It gets awfully dark ahead, so it'll be\n"
	.string "tough exploring without a light source.\p"
	.string "That person who came earlier…\n"
	.string "STEVEN I think it was. He knew how to\l"
	.string "use FLASH so he must be alright.\p"
	.string "By the way, you are {PLAYER}, right?\n"
	.string "I'm one of PROF. BIRCH assistants.$"

ScientistAssistant_Text_AssistantExplainFlash:
	.string "Any POKéMON able to learn it can use it\n"
	.string "to light up even the inky darkness\l"
	.string "of caves.\p"
	.string "But, to use it that way, you need the\n"
	.string "GYM BADGE from DEWFORD's POKéMON GYM.$"

ScientistAssistant_Text_AssistantAfterGivingFlash:
	.string "Though you may manage to advance\n"
	.string "in a dark cave somehow, having\l"
	.string "some light with you never comes\l"
	.string "bad if you don't know the way.$"

ScientistAssistant_Text_AssistantPreRockSmash:
	.string "There are some rocks blocking the path\n"
	.string "on ROUTE 111.\p"
	.string "If you don't manage to do something\n"
	.string "with them, you can't get through\l"
	.string "to ROUTE 112.\p"
	.string "By the way, you are {PLAYER}, right?\n"
	.string "I'm one of PROF. BIRCH assistants.$"

ScientistAssistant_Text_AssistantExplainRockSmash:
	.string "That HM contains ROCK SMASH.\n"
	.string "To use it outside battle, you first\l"
	.string "need to get MAUVILLE GYM BADGE."
	.string "If you come across large boulders\n"
	.string "that block your path…\p"
	.string "Well, use that HM move and smash\n"
	.string "them right out of your way!\p"
	.string "Yes, sir! Smash rocks aside, I say!\n"
	.string "Woohoo!$"

ScientistAssistant_Text_AssistantAfterGivingRockSmash:
	.string "Oh, yes, if you smash a rock, a POKéMON\n"
	.string "could come flying out of hiding.\p"
	.string "Woohoo!$"

ScientistAssistant_Text_AssistantPreWaterfall:
	.string "There's a big waterfall to the east of\n"
	.string "ROUTE 128 which leads to\l"
	.string "EVER GRANDE CITY.\p"
	.string "The best POKéMON TRAINERS of HOENN\n"
	.string "gather there to challenge the\l"
	.string "POKéMON LEAGUE and show their might.$"

ScientistAssistant_Text_AssistantExplainWaterfall:
	.string "That HIDDEN MACHINE contains\n"
	.string "WATERFALL.\p"
	.string "If you have the RAIN BADGE, a POKéMON\n"
	.string "that can learn that HM move could\l"
	.string "force its way up waterfalls.\p"
	.string "By the way, you are {PLAYER}, right?\n"
	.string "I'm one of PROF. BIRCH assistants.$"

ScientistAssistant_Text_AssistantAfterGivingWaterfall:
	.string "Unreachable previous water places\n"
	.string "are now within reach with WATERFALL.$"

ScientistAssistant_Text_AssistantPreDive:
	.string "Though the humans have been able to\n"
	.string "watch things to astronomical distances\l"
	.string "from here, we are still ignorant about\l"
	.string "many of the secrets of the depths\l"
	.string "of the seas of our own planet.\p"
	.string "By the way, you are {PLAYER}, right?\n"
	.string "I'm one of PROF. BIRCH assistants.$"

ScientistAssistant_Text_AssistantExplainDive:
	.string "It's the HIDDEN MACHINE DIVE.\p"
	.string "While you're using SURF, you\l"
	.string "should notice dark patches of water.\p"
	.string "Use DIVE if you come to deep water\n"
	.string "like it. You'll drop to the seafloor.\p"
	.string "When you want to come back up, use\n"
	.string "DIVE again.\p"
	.string "In some places, it won't be possible\n"
	.string "for you to surface, though.$"

ScientistAssistant_Text_AssistantAfterGivingDive:
	.string "Little we know about the deep undersea\n"
	.string "waters.\p"
	.string "I'm always excited about new\n"
	.string "discoverings in this places.$"
	