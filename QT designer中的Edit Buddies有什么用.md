QT designer中的Edit Buddies有什么用？

这个是用于设置QLabel的buddy的。

在这个模式下，可以把QLabel跟其它控件连起来。QLabel可以设置快捷键，当按下快捷键后，窗口焦点就移动到与它连接扩控件上。

比如一个QLabel显示的是“用户名(&U)”,这表示Alt+U是快捷键。如果设置Buddy时把它跟一个输入框连接了，那么按了Alt+U的话，输入框就获得了焦点。
