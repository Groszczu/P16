# Pad do gry Don't Starve
## Efekt końcowy

<p align="center">
  <img src="/images/without_case.jpg" width="400" title="without-case">
  <img src="/images/back.jpg" width="400" title="back">
  <img src="/images/front.jpg" width="500" title="front">
</p>

### [Efekt w grze Don't Starve](https://drive.google.com/file/d/1L8Kr0ft3-i-alJvvkAMZOxpQ4YpjElGc/view?usp=sharing)

## O projekcie
### Celem projektu było stworzenie kontrolera kompatybilnego z grą Don't Starve
### Do Realizacj kontrolera wykorzystano:
* Mikrokontoler STM32F407G-DISC1
* 2x Moduł 5 IO Keypad (700646947690), [schemat](https://www.waveshare.com/w/upload/f/fb/5-IO-Keypad-Schematic.pdf)
* Powerbank zasilający mikrokontroler

Software programu został napisany w języku C.</br>
Obudowa oraz przyciski zostały wydrukowane przy użyciu drukarki 3D.

Dane o stanie przycisków oraz joysticków są przesyłane do podłączonego urządzenia, w sześciu bajtach, zgodnie ze schematem:

<p align="center">
  <img src="/images/report-schema.png" width="500" title="report-schema">
</p>

Informacja o schemacie przesyłanego raportu została zakodowana przy pomocy następującego deskryptora USB:

```c
  /* USER CODE BEGIN 0 */
		  0x05, 0x01,                //USAGE_PAGE (Generic Desktop)
		  0x09, 0x05,                //USAGE (Game Pad)
		  0xa1, 0x01,                //COLLECTION (APPLICATION)
		  0xa1, 0x00,                   //COLLECTION (Physical)
		  0x05, 0x09,                   //USAGE_PAGE (Button)
		  0x19, 0x01,                   //USAGE_MINIMUM (Button1)
		  0x29, 0x18,                   //USAGE_MAXIMUM (Button 24)
		  0x15, 0x00,                   //LOGICAL_MINIMUM (0)
		  0x25, 0x01,                   //LOGICAL_MAXIMUM(1)
		  0x95, 0x18,                   //REPORT_COUNT (24)
		  0x75, 0x01,                   //REPORT_SIZE (1)
		  0x81, 0x02,                   //INPUT(Data, Var, Abs)
		  0x05, 0x01,                   //USAGE_PAGE (Generic Desktop)
		  0x09, 0x30,                   //USAGE (X)
		  0x09, 0x31,                   //USAGE (Y)
		  0x09, 0x32,                   //USAGE (Z)
		  0x09, 0x33,                   //USAGE (Rx)
		  0x15, 0x81,                   //LOGICAL_MINIMUM(-127)
		  0x25, 0x7f,                   //LOGICAL_MAXIMUM(127)
		  0x75, 0x08,                   //REPORT_SIZE(8)
		  0x95, 0x04,                   //REPORT_COUNT(4)
		  0x81, 0x02,                   //INPUT(Data,Var,Abs)
		  0xc0,                     //END_Collection
  /* USER CODE END 0 */
  0xC0    /*     END_COLLECTION	             */
```

Raport jest wysyłany do urządzenia po wykryciu wciśnięcia przycisku lub wychylenia drążka.

## Konfiguracja
### Konfiguracja pinów STM32

Do obsługi modułów 5 IO Keypad wykorzystano po 5 pinów:
* Piny PB11-PB15 - lewy moduł (GPIO)
* Piny PD0-PD3 oraz PD6 - prawy moduł (GPIO)

Piny wykorzystane do obsługi USB HID:
* PA11 i PA12

<p align="center">
  <img src="/images/pin-config.png" width="750" title="pin-config">
</p>

### Konfiguracja Big Picture 

Konfiguracje przycisków przeprowadzono wykorzystując oprogramowanie Big Picture dostępne w platformie Steam.

#### Kontroler wykryty w Big Picture

<p align="center">
  <img src="/images/in-big-picture.png" width="500" title="in-big-picture">
</p>

#### Przykładowa konfiguracja przycisków w Big Picture

<p align="center">
  <img src="/images/config-1.png" width="500" title="config-1">
  <img src="/images/config-2.png" width="500" title="config-2">
</p>

## Autorzy
* Roch Goszczyński
* Artur Jackowiak
> 2020 PUT

