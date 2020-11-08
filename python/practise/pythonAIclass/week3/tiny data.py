import numpy as np
import scipy.special
import matplotlib.pyplot
#%matplotlib inline

class neuralNetwork:

    def __init__(self, inputnodes, hiddennodes, outputnodes, learningrate):
        self.inodes = inputnodes
        self.hnodes = hiddennodes
        self.onodes = outputnodes

        self.lr = learningrate

        self.activation_function = lambda x:scipy.special.expit(x)

        self.w_ih = (np.random.rand(self.hnodes, self.inodes)-0.5)
        self.w_ho = (np.random.rand(self.onodes, self.hnodes)-0.5)
        pass

    def train(self,inputs_list, targets_list):
        inputs = np.array(inputs_list, ndmin=2).T
        targets = np.array(targets_list, ndmin=2).T

        hidden_inputs = np.dot(self.w_ih,inputs)
        hidden_outputs = self.activation_function(hidden_inputs)

        final_inputs = np.dot(self.w_ho,hidden_outputs)
        final_outputs = self.activation_function(final_inputs)

        outputs_errors = targets - final_outputs
        hidden_errors = np.dot(self.w_ho.T, outputs_errors)

        self.w_ho+=self.lr*np.dot((outputs_errors*final_outputs*(1.0-final_outputs)),np.transpose(hidden_outputs))
        self.w_ih+=self.lr*np.dot((hidden_errors*hidden_outputs*(1.0-hidden_outputs)),np.transpose(inputs))

        pass

    def query(self,inputs_list):
        inputs = np.array(inputs_list,ndmin=2).T

        hidden_inputs = np.dot(self.w_ih,inputs)
        hidden_outputs = self.activation_function(hidden_inputs)

        final_inputs = np.dot(self.w_ho,hidden_outputs)
        final_outputs = self.activation_function(final_inputs)

        return final_outputs

input_nodes = 784
hidden_nodes = 200
output_nodes = 10
learning_rate = 0.1
n=neuralNetwork(input_nodes,hidden_nodes,output_nodes,learning_rate)

trainning_data_file = open("train.csv",'r')
trainning_data_list = trainning_data_file.readlines()
trainning_data_file.close()

epochs = 5 #训练次数

for e in range(epochs):
    for record in trainning_data_list:
        all_values = record.split(",")
        inputs = (np.asfarray(all_values[1:]))
        targets = np.zeros(output_nodes)+0.01
        targets[int(all_values[0])] = 0.99
        n.train(inputs, targets)
        pass
    pass

test_data_file = open("test.csv",'r')
test_data_list = test_data_file.readlines()
test_data_file.close()

scorecard = []

for record in test_data_list:
    all_values = record.split(',')
    correct_label = int(all_values[0])

    inputs = (np.asfarray(all_values[1:]))
    outputs = n.query(inputs)

    label = np.argmax(outputs)

    if(label==correct_label):
        scorecard.append(1)
    else:
        scorecard.append(0)
        pass

    pass

print(scorecard)
