# <center>小型四倾转旋翼模型机

# (a small scale quad-tilt-rotor prototype)<center>  

&emsp;&emsp; 该项目资助来源于哈工程 (HEU) 自动化学院 2017年的大学生创新创业训练计划的项目，项目经费1万元左右，后该项目延续为我的本科毕业设计。启发来源于美国”鱼鹰V-22“倾转旋翼机和中国在研的“蓝鲸”四倾转旋翼机。由于经费有限，时间有限，资料有限，当时的个人能力有限，仅完成模型机的初步实现，包括：机械模型的设计制作（感谢EV刘同学的帮助），整体电控系统的设计，一个简单的地面站上位机（感谢EV燕同学的帮助），基于Free-RTOS的飞控开发，Hovering控制器设计、仿真和实现，倾转过渡模式的控制策略的仿真，进行了hovering模式下的飞行试验。后来由于飞行试验过程中的事故，导致模型部分损毁，由于没有时间和经费修复，研究就此终止，成为遗憾。

***

&emsp;&emsp;这是我本科所有科创项目中最综合的一个，由于大家当时都很忙，除了必要的帮忙，我几乎一个人承担机械、电控、仿真、软件和试验测试，所以部分工作实在显得简陋。努力总结出几点特色：

* 该项目里对部分元件，如电机，舵机等建模过程有详细描述，可以参考。

* 飞行控制还是常规双环PID，不过不是none-model的调参，对系统做了简单的建模，基于简化线性传函，在simulink中做了仿真，给实际的控制器参数提供参考。

* 模型机结构做的很差，倾转机构没找到特别好的方案，也没人帮忙，只能用大扭矩舵机，导致整机重量偏重，不过这种构型应该是可以进一步测试的。

* 整个电控系统是自己开发的，包括元件选型，PCB的设计焊接等，系统分成控制器板和电源板两部分，控制板（MCU是STM32F407VE）专门处理飞控程序，留有各种传感器接口，电源板集成了电流采样、强电隔离、控制电稳压等电路。无刷电机，电调，AHRS均使用淘宝模块，外加了蓝牙模块用来调试是存数据。

* 关于倾转策略，当时想了一个“非负攻角加速”的策略，先在直升机状态下倾转转子同时调整俯仰角到某一临界角度，然后再加速，使气动力逐渐发挥作用。但是没看到相关文献，自认为是奇思妙想，虽然没能通过实飞测试，但做了半实物仿真。至于现在有没有人做了相关工作，也没有再过多关注。

  总体来说，整个项目也算尽力去做了，但最大的不足还是在机械结构的设计和制作上，这也是倾转旋翼机的最大的难点之一，现阶段感觉可能尾座式无人机（tail-sitter）可能更有希望推广应用。

  ***

  该项目文件夹说明：

  * /code 里是项目设计的全部代码，包括整机飞控，组件的建模调试等，C语言编写，开发环境是针对stm32单片机的IDE软件keil5。（当时水平较菜，代码可能有些凌乱）
  * /document 里是项目的论文，包括毕设论文和答辩PPT，还有一篇为大创项目结题为拼凑的一篇小论文（并没有投任何刊物）。
  * /experiment data 里是实物建模和飞行测试的数据及其分析。
  * /PCB 里是两块电路板的原理图.
  * /picture&video 里是模型机相关的图片和测试视频。
  * /simulation 里是论文中对应的控制理论仿真设计内容，主要是各控制通道的simulink框图仿真和曲线绘图。
  
  ***
  
  感兴趣的同学想要进一步了解项目详情，可以联系我：yaokunz@hust.edu.cn
