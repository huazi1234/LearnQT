QT designer中的Edit Buddies有什么用？

这个是用于设置QLabel的buddy的。

在这个模式下，可以把QLabel跟其它控件连起来。QLabel可以设置快捷键，当按下快捷键后，窗口焦点就移动到与它连接扩控件上。

比如一个QLabel显示的是“用户名(&U)”,这表示Alt+U是快捷键。如果设置Buddy时把它跟一个输入框连接了，那么按了Alt+U的话，输入框就获得了焦点。




在Qt Designer的Edit菜单下有个Edit Buddies（编辑伙伴关系）子菜单，该菜单的作用是将一个Label与其他控件关联起来，当Label控件设置了快捷键时，通过Label的快捷键就可以直接使关联控件获得焦点。操作步骤如下：
1、通过在标签文本中使用"&字母"给标签设置快捷键，对应快捷键为：Alt+字母；
2、选择标签，点击Edit Buddies子菜单，或先点击Edit Buddies子菜单再选择标签后，单击这个标签并把红色箭头拖到对应要关联的控件上,释放鼠标按键，就会出现一根从标签到控件的红色单向箭头，此时两个控件就建立了关联，按ESC或者点击Edit的其他子菜单就会离开这种设置模式。
下图是一个进入Edit Buddies模式的案例：


下图是上图设置完成后进入标签编辑时的截图：

————————————————
版权声明：本文为CSDN博主「laoyuanpython」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/LaoYuanPython/article/details/101909730



只有QLabel 标签对象才可以有伙伴窗口对象，也只有该QLabel对象具有快捷键。

快捷键设置方法：在显示文本的某个字符的前面加一个前缀“&” 就可以定义快捷键了



 

 1 Dialog::Dialog(QWidget *parent)
 2     : QDialog(parent)
 3 {
 4     label1 = new QLabel(this);
 5     label1->setText(tr("请输入圆的半径： "));
 6     lineEdit = new QLineEdit(this);
 7     label2 = new QLabel(this);
 8     button = new QPushButton(this);
 9     button->setText(tr("显示对应的圆面积"));
10 
11     nameLabel = new QLabel("&Name",this);
12     nameEdit = new QLineEdit(this);
13     nameLabel->setBuddy(nameEdit);
14 
15     phoneLabel = new QLabel("&Phone",this);
16     phoneEdit = new QLineEdit(this);
17     phoneLabel->setBuddy(phoneEdit);
18 
19     QGridLayout * mainLayout = new QGridLayout(this);
20     mainLayout->addWidget(label1,0,0);
21     mainLayout->addWidget(lineEdit,0,1);
22     mainLayout->addWidget(label2,1,0);
23     mainLayout->addWidget(button,1,1);
24 
25     mainLayout->addWidget(nameLabel,2,0);
26     mainLayout->addWidget(nameEdit,2,1);
27     mainLayout->addWidget(phoneLabel,3,0);
28     mainLayout->addWidget(phoneEdit,3,1);
29 
30     connect(button,SIGNAL(clicked()),this,SLOT(showArea()));
31 }
