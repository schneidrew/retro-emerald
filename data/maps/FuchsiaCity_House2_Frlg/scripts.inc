FuchsiaCity_House2_Frlg_MapScripts::
	.byte 0

FuchsiaCity_House2_EventScript_FishingGurusBrother::
	lock
	faceplayer
	msgbox FuchsiaCity_House2_Text_FishingAdvice
	release
	end

FuchsiaCity_House2_Text_FishingAdvice::
	.string "Fishing is a way of life!\n"
	.string "It is like the finest poetry.\p"
	.string "Wherever there's water, try your luck\n"
	.string "at fishing.$"
