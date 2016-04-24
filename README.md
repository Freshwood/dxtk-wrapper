The dxtk-wrapper repo
===================

What is this repo for?

#### With this c++ native **lib** you can easily use directx 11 functions.
#### Here is a list of the current implemented functions

-  DrawOutlinedText

-  DrawOutlinedTextEx

-  DrawDxText

-  GradientRectangle

-  DrawBorder

-  DrawRectangle

-  DrawBox

-  DrawBoxGradient

-  DrawLine

-  DrawHealthBar

-  DrawBoundingBox

-  DrawCrosshair

-  retScreenWidth

-  retScreenHeight

----------


Prerequisite
-------------

> **Note:**

> - You need a directx11 device and a directx11 device context
> - https://msdn.microsoft.com/de-de/library/windows/desktop/ff476379(v=vs.85).aspx
> - https://msdn.microsoft.com/en-us/library/windows/desktop/ff476385(v=vs.85).aspx
> Normaly you have the device and context, when you create a directx11 application
> or you are hooking are directx11 app. *(e.g. a dx11 game)*


Usage
-------------------

- Download the latest release or bind the source to your project
- Make sure you put content from the *\Resource* folder to *C:\\*
- Add the *\Inc* folder to the additional includes
- Make sure you use the **.lib* as a reference