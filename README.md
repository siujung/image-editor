# image-editor
GIMP-like image and video editor with facial recognition using opencv.

GUI made with cvui.

Takes image and video file name as input by command line (file must be in the project directory).

Includes the following image editing functions:
dilate, erode, resize, lighten/darken, contrast, rotate, blur, gaussian blur, canny edge.

Can access webcam using camera button.

The face button searches for a face on current image (captures current image when webcam is used).

User may train the face recognizer by:
- clicking on the blue square of the recognized face.
- giving the name of the face as input by command line.
