//ali

#include <assert.h>
#include <iostream>
#include <vector>
#include "tensorflow/c/c_api.h"
//#include "display.h"
//class  Dragon_TFSession;
        
class  Dragon_TFSession
{
 public:       
	TF_Session* session;
	int ninputs;
        float *pdata;
	int noutputs;
	std::vector<TF_Output> inputs;
	std::vector<TF_Tensor*> input_values;
	std::vector<TF_Output> outputs;
	std::vector<TF_Tensor*> output_values;
	std::vector<TF_Output> inputs2;
	std::vector<TF_Tensor*> input_values2;

	Dragon_TFSession()      {}
	~Dragon_TFSession() ;    
	
	
	
	int LoadGraph(float *pfdata);
	int RunSession(void);
};
TF_Buffer* read_file(const char* file); 
	
