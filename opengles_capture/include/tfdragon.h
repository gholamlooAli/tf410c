//ali

#include <assert.h>
#include <iostream>
#include <vector>
#include "tensorflow/c/c_api.h"
#include "display.h"
class  Dragon_TFSession;
        
class  Dragon_TFSession
{
 public:       
	TF_Session* session;
	//const TF_Output* inputs;
	//TF_Tensor* const* input_values;
	int ninputs;
        float *pdata;
	//const TF_Output* outputs;
	//TF_Tensor** output_values;
	int noutputs;
	std::vector<TF_Output> inputs;
	std::vector<TF_Tensor*> input_values;
	std::vector<TF_Output> outputs;
	std::vector<TF_Tensor*> output_values;
	

	Dragon_TFSession()      {}
	~Dragon_TFSession()     {}
	int LoadGraph(float *pfdata);
};
TF_Buffer* read_file(const char* file); 
	
