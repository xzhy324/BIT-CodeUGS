import numpy
import scipy.special
import scipy.ndimage
import matplotlib.pyplot
import imageio
import glob
import pylab
#%matplotlib inline

class neuralNetwork:

    def __init__(self,inputnodes,hiddennodes,outputnodes,learningrate):
        self.inodes = inputnodes
        self.hnodes = hiddennodes
        self.onodes = outputnodes


        self.wih = numpy.random.normal(0.0,pow(self.inodes,-0.5), (self.hnodes,self.inodes))
        self.who = numpy.random.normal(0.0,pow(self.hnodes,-0.5), (self.onodes,self.hnodes))

        self.lr = learningrate
        self.activation_function = lambda x:scipy.special.expit(x)

        pass


    def train(self,inputs_list,targets_list):

        inputs = numpy.array(inputs_list,ndmin=2).T
        targets = numpy.array(targets_list,ndmin=2).T

        hidden_inputs = numpy.dot(self.wih,inputs)
        hidden_outputs = self.activation_function(hidden_inputs)

        final_inputs = numpy.dot(self.who,hidden_outputs)
        final_outputs = self.activation_function(final_inputs)

        output_errors = targets-final_outputs
        hidden_errors = numpy.dot(self.who.T, output_errors)

        self.who +=self.lr*numpy.dot((output_errors*final_outputs*(1.0-final_outputs)), numpy.transpose(hidden_outputs))
        self.wih +=self.lr*numpy.dot((hidden_errors*hidden_outputs*(1.0-hidden_outputs)), numpy.transpose(inputs))

        pass


    def query(self,inputs_list):
        inputs = numpy.array(inputs_list,ndmin=2).T
        hidden_inputs = numpy.dot(self.wih,inputs)
        hidden_outputs = self.activation_function(hidden_inputs)

        final_inputs = numpy.dot(self.who,hidden_outputs)
        final_outputs = self.activation_function(final_inputs)
        return final_outputs



input_nodes = 784
hidden_nodes = 200
output_notes = 10

learningrate = 0.1

n = neuralNetwork(input_nodes,hidden_nodes,output_notes,learningrate)

training_data_file = open("test.csv",'r')
training_data_list = training_data_file.readlines()
training_data_file.close



epochs = 10
for e in range(epochs):
    for record in training_data_list:
        all_values = record.split(',')
        inputs = (numpy.asfarray(all_values[1:])/255.0*0.99)+0.01
        targets = numpy.zeros(output_notes)+0.01
        targets[int(all_values[0])] = 0.99
        n.train(inputs,targets)

        inputs_plusx_img = scipy.ndimage.interpolation.rotate(inputs.reshape(28,28),10,cval=0.01,order=1,reshape=False)
        n.train(inputs_plusx_img.reshape(784),targets)

        inputs_minusx_img = scipy.ndimage.interpolation.rotate(inputs.reshape(28,28),10,cval=0.01,order=1,reshape=False)
        n.train(inputs_minusx_img.reshape(784),targets)

        pass
    pass

test_data_file = open("train.csv",'r')
test_data_list = test_data_file.readlines()
test_data_file.close()

scorecard = []
for record in test_data_list:
    all_values = record.split(',')
    correct_label = int(all_values[0])
    inputs = (numpy.asfarray(all_values[1:])/255.0*0.99)+0.01
    outputs = n.query(inputs)

    label = numpy.argmax(outputs)
    if(label == correct_label):
        scorecard.append(1)
    else:
        scorecard.append(0)
        pass
    pass

#print(scorecard)
    #scorecard_array =numpy.asarray(scorecard)
scorecard_array = numpy.asarray(scorecard)
print("performance = ",scorecard_array.sum()/scorecard_array.size)
