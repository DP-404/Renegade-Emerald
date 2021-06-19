.set LOCALID_SAILOR, 1
.set LOCALID_SS_TIDAL, 2

DewfordTown_Harbor_MapScripts:: @ 826805C
	.byte 0

DewfordTown_Harbor_EventScript_Sailor:: @ 826805D
	lock
	faceplayer
	msgbox DewfordTown_Harbor_Text_SailorReturn, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq DewfordTown_Harbor_EventScript_FineTakeYourTime
	msgbox DewfordTown_Harbor_Text_SailSlateport, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 30
	hideobjectat LOCALID_SAILOR, MAP_DEWFORD_TOWN_HARBOR
	setvar VAR_0x8004, LOCALID_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	warp MAP_SLATEPORT_CITY_HARBOR, 255, 8, 11
	waitstate
	release
	end

DewfordTown_Harbor_EventScript_FineTakeYourTime:: @ 82680A2
	msgbox DewfordTown_Harbor_Text_FineTakeYourTime, MSGBOX_DEFAULT
	release
	end

DewfordTown_Harbor_Text_SailSlateport:
	.string "Alright, we're sailing for\n"
	.string "SLATEPORT CITY.$"

DewfordTown_Harbor_Text_SailorReturn:
	.string "Shall we return to SLATEPORT CITY?$"

DewfordTown_Harbor_Text_FineTakeYourTime:
	.string "Fine, take your time.\p"
	.string "When you want to return just\n"
	.string "show yourself around here.$"
