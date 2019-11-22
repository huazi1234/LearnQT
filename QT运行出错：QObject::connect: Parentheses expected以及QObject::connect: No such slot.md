QT运行出错：QObject::connect: Parentheses expected以及QObject::connect: No such slot ***
我在QGraphicsScene子类中添加了item的弹出菜单，并连接Action到槽函数，结果槽函数不起作用，输出：QObject::connect: No such slot ***

在类中使用信号/槽时一定要加Q_OBJECT宏，signal和slots的参数要一样

槽函数加()： connect(toTopLayerAction, SIGNAL(triggered()), this, SLOT(slotLayerTop()));   // 正确

切记忘了()：connect(toTopLayerAction, SIGNAL(triggered()), this, SLOT(slotLayerTop));      // 错误

希望大家能把自己的所学和他人一起分享，不要去鄙视别人索取时的贪婪，因为最应该被鄙视的是不肯分享时的吝啬。
