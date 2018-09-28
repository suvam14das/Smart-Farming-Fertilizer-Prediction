'''
####################################################################################################################################

GUI
Tools : tkinter

Code developed by : Suvam Das & Sougata Hanra
github : @suvam14das, @hanras97

####################################################################################################################################

'''
import tensorflow as tf 
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
from tkinter import *
import FertPredict_g

root = Tk()
t1,t2,t3,t4,t5,t6,t7,t8,t9=0,0,0,0,0,0,0,0,0
xin = tf.placeholder('float',[None, 9])
yin = tf.placeholder('float')

def pressbutton():
	t1 = float(f1.get())
	t2 = float(f2.get())
	t3 = float(f3.get())
	t4 = float(f4.get())
	t5 = float(f5.get())
	t6 = float(f6.get())
	t7 = float(f7.get())
	t8 = float(f8.get())
	t9 = float(f9.get())

	s = FertPredict_g.train_neural_network(xin,[t1,t2,t3,t4,t5,t6,t7,t8,t9])
	label_pred = Label(bottomframe,text=s,bg='violet',font="Helvetica 15 bold").grid(row=12, column=4)


f1 = StringVar()
f2 = StringVar()
f3 = StringVar()
f4 = StringVar()
f5 = StringVar()
f6 = StringVar()
f7 = StringVar()
f8 = StringVar()
f9 = StringVar()

root.geometry("450x450")
root.title("FertPredict")
root.resizable(0,0)
topframe = Frame(root,bg='violet')
topframe.pack_propagate(0)
topframe.pack(fill="both")
bottomframe = Frame(root,bg='violet')
bottomframe.pack_propagate(0)
bottomframe.pack(fill="both", expand=1)
thelabel = Label(topframe,text="       Fertilizer Predictor",fg="blue",bg='violet',font="Helvetica 20")
thelabel.grid(pady=50,sticky="we")


label_1 = Label(bottomframe,text="              Crop :",height=1,bg='violet',font="Helvetica 15 bold").grid(row=1,column=2,sticky=E)
label_2 = Label(bottomframe,text="Month :",height=1,bg='violet',font="Helvetica 15 bold").grid(row=2,column=2,sticky=E)
entry_1 = Entry(bottomframe,textvariable=f1,width=10).grid(row=1,column=4,sticky=W,padx=10)
entry_2 = Entry(bottomframe,textvariable=f2,width=10).grid(row=2,column=4,sticky=W,padx=10)
label_3 = Label(bottomframe,text="Potassium :",height=1,bg='violet',font="Helvetica 15 bold").grid(row=3,column=2,sticky=E)
label_4 = Label(bottomframe,text="Sulfur :",height=1,bg='violet',font="Helvetica 15 bold").grid(row=4,column=2,sticky=E)
entry_3 = Entry(bottomframe,textvariable=f3,width=10).grid(row=3,column=4,sticky=W,padx=10)
entry_4 = Entry(bottomframe,textvariable=f4,width=10).grid(row=4,column=4,sticky=W,padx=10)
label_5 = Label(bottomframe,text="Nitrogen :",height=1,bg='violet',font="Helvetica 15 bold").grid(row=5,column=2,sticky=E)
label_6 = Label(bottomframe,text="Lime Index :",height=1,bg='violet',font="Helvetica 15 bold").grid(row=6,column=2,sticky=E)
entry_5 = Entry(bottomframe,textvariable=f5,width=10).grid(row=5,column=4,sticky=W,padx=10)
entry_6 = Entry(bottomframe,textvariable=f6,width=10).grid(row=6,column=4,sticky=W,padx=10)
label_7 = Label(bottomframe,text="Carbon :",height=1,bg='violet',font="Helvetica 15 bold").grid(row=7,column=2,sticky=E)
label_8 = Label(bottomframe,text="Phosphorous :",height=1,bg='violet',font="Helvetica 15 bold").grid(row=8,column=2,sticky=E)
entry_7 = Entry(bottomframe,textvariable=f7,width=10).grid(row=7,column=4,sticky=W,padx=10)
entry_8 = Entry(bottomframe,textvariable=f8,width=10).grid(row=8,column=4,sticky=W,padx=10)
label_9 = Label(bottomframe,text="Soil Moisture :",height=1,bg='violet',font="Helvetica 15 bold").grid(row=9,column=2,sticky=E)
entry_9 = Entry(bottomframe,textvariable=f9,width=10).grid(row=9,column=4,sticky=W,padx=10)

label_10 = Label(bottomframe,height=3,bg='violet').grid(row=11)

button = Button(bottomframe,text="Predict",width=15,height=1,command=pressbutton).grid(row=12,column=2,sticky=E)

root.mainloop()
