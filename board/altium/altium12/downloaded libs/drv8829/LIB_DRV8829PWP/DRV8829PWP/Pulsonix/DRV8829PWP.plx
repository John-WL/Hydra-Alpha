PULSONIX_LIBRARY_ASCII "SamacSys ECAD Model"
//414251/453108/2.49/28/3/Motor

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r147.5_45"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 0.45) (shapeHeight 1.475))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(textStyleDef "Normal"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 1.27)
			(strokeWidth 0.127)
		)
	)
	(patternDef "SOP65P640X120-28N" (originalName "SOP65P640X120-28N")
		(multiLayer
			(pad (padNum 1) (padStyleRef r147.5_45) (pt -2.938, 4.225) (rotation 90))
			(pad (padNum 2) (padStyleRef r147.5_45) (pt -2.938, 3.575) (rotation 90))
			(pad (padNum 3) (padStyleRef r147.5_45) (pt -2.938, 2.925) (rotation 90))
			(pad (padNum 4) (padStyleRef r147.5_45) (pt -2.938, 2.275) (rotation 90))
			(pad (padNum 5) (padStyleRef r147.5_45) (pt -2.938, 1.625) (rotation 90))
			(pad (padNum 6) (padStyleRef r147.5_45) (pt -2.938, 0.975) (rotation 90))
			(pad (padNum 7) (padStyleRef r147.5_45) (pt -2.938, 0.325) (rotation 90))
			(pad (padNum 8) (padStyleRef r147.5_45) (pt -2.938, -0.325) (rotation 90))
			(pad (padNum 9) (padStyleRef r147.5_45) (pt -2.938, -0.975) (rotation 90))
			(pad (padNum 10) (padStyleRef r147.5_45) (pt -2.938, -1.625) (rotation 90))
			(pad (padNum 11) (padStyleRef r147.5_45) (pt -2.938, -2.275) (rotation 90))
			(pad (padNum 12) (padStyleRef r147.5_45) (pt -2.938, -2.925) (rotation 90))
			(pad (padNum 13) (padStyleRef r147.5_45) (pt -2.938, -3.575) (rotation 90))
			(pad (padNum 14) (padStyleRef r147.5_45) (pt -2.938, -4.225) (rotation 90))
			(pad (padNum 15) (padStyleRef r147.5_45) (pt 2.938, -4.225) (rotation 90))
			(pad (padNum 16) (padStyleRef r147.5_45) (pt 2.938, -3.575) (rotation 90))
			(pad (padNum 17) (padStyleRef r147.5_45) (pt 2.938, -2.925) (rotation 90))
			(pad (padNum 18) (padStyleRef r147.5_45) (pt 2.938, -2.275) (rotation 90))
			(pad (padNum 19) (padStyleRef r147.5_45) (pt 2.938, -1.625) (rotation 90))
			(pad (padNum 20) (padStyleRef r147.5_45) (pt 2.938, -0.975) (rotation 90))
			(pad (padNum 21) (padStyleRef r147.5_45) (pt 2.938, -0.325) (rotation 90))
			(pad (padNum 22) (padStyleRef r147.5_45) (pt 2.938, 0.325) (rotation 90))
			(pad (padNum 23) (padStyleRef r147.5_45) (pt 2.938, 0.975) (rotation 90))
			(pad (padNum 24) (padStyleRef r147.5_45) (pt 2.938, 1.625) (rotation 90))
			(pad (padNum 25) (padStyleRef r147.5_45) (pt 2.938, 2.275) (rotation 90))
			(pad (padNum 26) (padStyleRef r147.5_45) (pt 2.938, 2.925) (rotation 90))
			(pad (padNum 27) (padStyleRef r147.5_45) (pt 2.938, 3.575) (rotation 90))
			(pad (padNum 28) (padStyleRef r147.5_45) (pt 2.938, 4.225) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0, 0) (textStyleRef "Normal") (isVisible True))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -3.925 5.15) (pt 3.925 5.15) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 3.925 5.15) (pt 3.925 -5.15) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 3.925 -5.15) (pt -3.925 -5.15) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -3.925 -5.15) (pt -3.925 5.15) (width 0.05))
		)
		(layerContents (layerNumRef 28)
			(line (pt -2.2 4.85) (pt 2.2 4.85) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 2.2 4.85) (pt 2.2 -4.85) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 2.2 -4.85) (pt -2.2 -4.85) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -2.2 -4.85) (pt -2.2 4.85) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -2.2 4.2) (pt -1.55 4.85) (width 0.025))
		)
		(layerContents (layerNumRef 18)
			(line (pt -1.85 4.85) (pt 1.85 4.85) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 1.85 4.85) (pt 1.85 -4.85) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 1.85 -4.85) (pt -1.85 -4.85) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -1.85 -4.85) (pt -1.85 4.85) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -3.675 4.8) (pt -2.2 4.8) (width 0.2))
		)
	)
	(symbolDef "DRV8829PWP" (originalName "DRV8829PWP")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 2) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 3) (pt 0 mils -200 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -225 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 4) (pt 0 mils -300 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -325 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 5) (pt 0 mils -400 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -425 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 6) (pt 0 mils -500 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -525 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 7) (pt 0 mils -600 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -625 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 8) (pt 0 mils -700 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -725 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 9) (pt 0 mils -800 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -825 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 10) (pt 0 mils -900 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -925 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 11) (pt 0 mils -1000 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -1025 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 12) (pt 0 mils -1100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -1125 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 13) (pt 0 mils -1200 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -1225 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 14) (pt 0 mils -1300 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -1325 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 15) (pt 1400 mils 0 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1170 mils -25 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 16) (pt 1400 mils -100 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1170 mils -125 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 17) (pt 1400 mils -200 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1170 mils -225 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 18) (pt 1400 mils -300 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1170 mils -325 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 19) (pt 1400 mils -400 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1170 mils -425 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 20) (pt 1400 mils -500 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1170 mils -525 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 21) (pt 1400 mils -600 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1170 mils -625 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 22) (pt 1400 mils -700 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1170 mils -725 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 23) (pt 1400 mils -800 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1170 mils -825 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 24) (pt 1400 mils -900 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1170 mils -925 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 25) (pt 1400 mils -1000 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1170 mils -1025 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 26) (pt 1400 mils -1100 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1170 mils -1125 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 27) (pt 1400 mils -1200 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1170 mils -1225 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 28) (pt 1400 mils -1300 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1170 mils -1325 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(line (pt 200 mils 100 mils) (pt 1200 mils 100 mils) (width 6 mils))
		(line (pt 1200 mils 100 mils) (pt 1200 mils -1400 mils) (width 6 mils))
		(line (pt 1200 mils -1400 mils) (pt 200 mils -1400 mils) (width 6 mils))
		(line (pt 200 mils -1400 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 1250 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))
		(attr "Type" "Type" (pt 1250 mils 200 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))

	)
	(compDef "DRV8829PWP" (originalName "DRV8829PWP") (compHeader (numPins 28) (numParts 1) (refDesPrefix M)
		)
		(compPin "1" (pinName "CP1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "2" (pinName "CP2") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "3" (pinName "VCP") (partNum 1) (symPinNum 3) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "4" (pinName "VM_1") (partNum 1) (symPinNum 4) (gateEq 0) (pinEq 0) (pinType Power))
		(compPin "5" (pinName "OUT1_1") (partNum 1) (symPinNum 5) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "6" (pinName "ISEN_1") (partNum 1) (symPinNum 6) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "7" (pinName "OUT2_1") (partNum 1) (symPinNum 7) (gateEq 0) (pinEq 0) (pinType Output))
		(compPin "8" (pinName "OUT2_2") (partNum 1) (symPinNum 8) (gateEq 0) (pinEq 0) (pinType Output))
		(compPin "9" (pinName "ISEN_2") (partNum 1) (symPinNum 9) (gateEq 0) (pinEq 0) (pinType Power))
		(compPin "10" (pinName "OUT1_2") (partNum 1) (symPinNum 10) (gateEq 0) (pinEq 0) (pinType Output))
		(compPin "11" (pinName "VM_2") (partNum 1) (symPinNum 11) (gateEq 0) (pinEq 0) (pinType Power))
		(compPin "12" (pinName "VREF_1") (partNum 1) (symPinNum 12) (gateEq 0) (pinEq 0) (pinType Input))
		(compPin "13" (pinName "VREF_2") (partNum 1) (symPinNum 13) (gateEq 0) (pinEq 0) (pinType Input))
		(compPin "14" (pinName "GND_1") (partNum 1) (symPinNum 14) (gateEq 0) (pinEq 0) (pinType Power))
		(compPin "28" (pinName "GND_2") (partNum 1) (symPinNum 15) (gateEq 0) (pinEq 0) (pinType Power))
		(compPin "27" (pinName "I4") (partNum 1) (symPinNum 16) (gateEq 0) (pinEq 0) (pinType Input))
		(compPin "26" (pinName "I3") (partNum 1) (symPinNum 17) (gateEq 0) (pinEq 0) (pinType Input))
		(compPin "25" (pinName "I2") (partNum 1) (symPinNum 18) (gateEq 0) (pinEq 0) (pinType Input))
		(compPin "24" (pinName "I1") (partNum 1) (symPinNum 19) (gateEq 0) (pinEq 0) (pinType Input))
		(compPin "23" (pinName "I0") (partNum 1) (symPinNum 20) (gateEq 0) (pinEq 0) (pinType Input))
		(compPin "22" (pinName "NC") (partNum 1) (symPinNum 21) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "21" (pinName "ENBL") (partNum 1) (symPinNum 22) (gateEq 0) (pinEq 0) (pinType Input))
		(compPin "20" (pinName "PHASE") (partNum 1) (symPinNum 23) (gateEq 0) (pinEq 0) (pinType Input))
		(compPin "19" (pinName "DECAY") (partNum 1) (symPinNum 24) (gateEq 0) (pinEq 0) (pinType Input))
		(compPin "18" (pinName "NFAULT") (partNum 1) (symPinNum 25) (gateEq 0) (pinEq 0) (pinType Output))
		(compPin "17" (pinName "NSLEEP") (partNum 1) (symPinNum 26) (gateEq 0) (pinEq 0) (pinType Input))
		(compPin "16" (pinName "NRESET") (partNum 1) (symPinNum 27) (gateEq 0) (pinEq 0) (pinType Input))
		(compPin "15" (pinName "V3P3OUT") (partNum 1) (symPinNum 28) (gateEq 0) (pinEq 0) (pinType Output))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "DRV8829PWP"))
		(attachedPattern (patternNum 1) (patternName "SOP65P640X120-28N")
			(numPads 28)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
				(padNum 3) (compPinRef "3")
				(padNum 4) (compPinRef "4")
				(padNum 5) (compPinRef "5")
				(padNum 6) (compPinRef "6")
				(padNum 7) (compPinRef "7")
				(padNum 8) (compPinRef "8")
				(padNum 9) (compPinRef "9")
				(padNum 10) (compPinRef "10")
				(padNum 11) (compPinRef "11")
				(padNum 12) (compPinRef "12")
				(padNum 13) (compPinRef "13")
				(padNum 14) (compPinRef "14")
				(padNum 15) (compPinRef "15")
				(padNum 16) (compPinRef "16")
				(padNum 17) (compPinRef "17")
				(padNum 18) (compPinRef "18")
				(padNum 19) (compPinRef "19")
				(padNum 20) (compPinRef "20")
				(padNum 21) (compPinRef "21")
				(padNum 22) (compPinRef "22")
				(padNum 23) (compPinRef "23")
				(padNum 24) (compPinRef "24")
				(padNum 25) (compPinRef "25")
				(padNum 26) (compPinRef "26")
				(padNum 27) (compPinRef "27")
				(padNum 28) (compPinRef "28")
			)
		)
		(attr "Manufacturer_Name" "Texas Instruments")
		(attr "Manufacturer_Part_Number" "DRV8829PWP")
		(attr "Mouser Part Number" "595-DRV8829PWP")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/Texas-Instruments/DRV8829PWP?qs=UlfnwZ2x8nTwexgNYqnN7g%3D%3D")
		(attr "Arrow Part Number" "DRV8829PWP")
		(attr "Arrow Price/Stock" "https://www.arrow.com/en/products/drv8829pwp/texas-instruments")
		(attr "Description" "5A Half Bipolar Stepper Motor Driver with 32-Level Current Regulation (PH/EN Ctrl)")
		(attr "<Hyperlink>" "http://www.ti.com/product/DRV8829/datasheet")
		(attr "<Component Height>" "1.2")
		(attr "<STEP Filename>" "DRV8829PWP.stp")
		(attr "<STEP Offsets>" "X=0;Y=0;Z=0")
		(attr "<STEP Rotation>" "X=0;Y=0;Z=0")
	)

)
