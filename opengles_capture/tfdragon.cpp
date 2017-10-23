//ali

#include <assert.h>
#include <iostream>
#include <vector>
#include "tensorflow/c/c_api.h"
#include "tfdragon.h"


void free_buffer(void* data, size_t length) {                                             
        free(data);  
}
TF_Buffer* read_file(const char* file) {                                                  
  FILE *f = fopen(file, "rb");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);                                                                  
  fseek(f, 0, SEEK_SET);  //same as rewind(f);                                            

  void* data = malloc(fsize);                                                             
  fread(data, fsize, 1, f);
  fclose(f);

  TF_Buffer* buf = TF_NewBuffer();                                                        
  buf->data = data;
  buf->length = fsize;                                                                    
  buf->data_deallocator = free_buffer;                                                    
  return buf;
} 

//Dragon_TFSession DrTfSession;
int Dragon_TFSession::RunSession(void)
{
	TF_Status* status = TF_NewStatus(); 
	TF_SessionRun(session, nullptr, &inputs[0], &input_values[0],ninputs,
			&outputs[0], &output_values[0], noutputs, nullptr, 0, nullptr, status);
	// Assign the values from the output tensor to a variable and iterate over them
	float* out_vals = static_cast<float*>(TF_TensorData(output_values[0]));
	if (TF_GetCode(status) != TF_OK) {
		  fprintf(stderr, "ERROR: Unable to run session %s", TF_Message(status));        
		  return -1;
	} 
			  
	float ress=*out_vals++;
	if(ress>0.59){		std::cout << "rose:" <<ress;	}
	ress=*out_vals++;
	if(ress>0.59){		std::cout << "dand:" <<ress;	}
	ress=*out_vals++;
	if(ress>0.59){		std::cout << "daisy:" <<ress;	}
	ress=*out_vals++;
	if(ress>0.59){		std::cout << "sunflower:" <<ress;	}
	ress=*out_vals++;
	if(ress>0.59){		std::cout << "tulips:" <<ress<<"\t";	}
			
		
	return 0;
}
Dragon_TFSession::~Dragon_TFSession()
{
	fprintf(stdout, "Successfully class Dragon_TFSession destructed\n");
	TF_Status* status = TF_NewStatus(); 
	TF_CloseSession( session, status );
	TF_DeleteSession( session, status );
  //TF_DeleteSessionOptions( sess_opts );      
	TF_DeleteStatus(status);
  //TF_DeleteImportGraphDefOptions(opts);
  //TF_DeleteGraph(graph);
	
}
//ali */
int Dragon_TFSession::LoadGraph(float* pfdata)
{
	//---------------------------------------------------------------------------------------
	// Graph definition from unzipped https://storage.googleapis.com/download.tensorflow.org/models/inception5h.zip
	// which is used in the Go, Java and Android examples                                   
	TF_Buffer* graph_def = read_file("/home/linaro/label/output_graph.pb");                      
	TF_Graph* graph = TF_NewGraph();
	pdata=pfdata;
	// Import graph_def into graph                                                          
	TF_Status* status = TF_NewStatus();                                                     
	TF_ImportGraphDefOptions* opts = TF_NewImportGraphDefOptions();                         
	TF_GraphImportGraphDef(graph, graph_def, opts, status);
	TF_DeleteImportGraphDefOptions(opts);
	if (TF_GetCode(status) != TF_OK) {
		fprintf(stderr, "ERROR: Unable to import graph %s", TF_Message(status));        
		return -1;
	}   	
TF_Operation* pp = TF_GraphOperationByName(graph, "MobilenetV1/Conv2d_0/weights");
inputs2.push_back({pp, 0});	
	fprintf(stdout, "Successfully imported graph=====%d\n",inputs2.size());
	// Add the placeholders you would like to feed, e.g.:
	TF_Operation* placeholder = TF_GraphOperationByName(graph, "input");
	inputs.push_back({placeholder, 0});
	ninputs=inputs.size();
	// Create a new tensor pointing to that memory:
	int 	inputwidth=224;
	int	inputheight=224;
	int 	*imNumPt = new int(1);
	const 	int64_t tensorDims[4] = {1,inputheight,inputwidth,3};
	const 	int 	num_bytes=inputheight * inputwidth * 3* sizeof(float);
	const 	int 	num_bytes_out = 5 * sizeof(float);

	int64_t out_dims[] = {1, 5};
	
	TF_Tensor* tensor = TF_NewTensor(TF_FLOAT, tensorDims, 4, pfdata,num_bytes , NULL, imNumPt);
	input_values.push_back(tensor);
	// Optionally, you can check that your input_op and input tensors are correct
	  // by using some of the functions provided by the C API.
	std::cout << "Input op info: " << TF_OperationNumOutputs(placeholder) << "\n";
	std::cout << "Input data info: " << TF_Dim(tensor, 0) << "\n";
	
	// Setup graph outputs
	TF_Operation* output_op = TF_GraphOperationByName(graph, "final_result");
	outputs.push_back({output_op, 0});
	output_values.resize(outputs.size(), nullptr);
	noutputs=outputs.size();
	// Similar to creating the input tensor, however here we don't yet have the
	// output values, so we use TF_AllocateTensor()
	TF_Tensor* output_value = TF_AllocateTensor(TF_FLOAT, out_dims, 2, num_bytes_out);
	output_values.push_back(output_value);

	// As with inputs, check the values for the output operation and output tensor
	std::cout << "Output: " << TF_OperationName(output_op) << "\n";
	std::cout << "Output info: " << TF_Dim(output_value, 0) << "\n";


	// Run `graph`
	TF_SessionOptions* sess_opts = TF_NewSessionOptions();
	session = TF_NewSession(graph, sess_opts, status);
	//assert(TF_GetCode(status) == TF_OK);
	if (TF_GetCode(status) != TF_OK) {
		  fprintf(stderr, "ERROR: Unable to new session %s", TF_Message(status));        
		  return 1;
	}
	fprintf(stdout, "Successfully new session was created\n");

}
	


  /*
TF_SessionRun(session, nullptr, &inputs[0], &input_values[0], inputs.size(),
              &outputs[0], &output_values[0], outputs.size(), nullptr, 0, nullptr, status);
  // Assign the values from the output tensor to a variable and iterate over them
  float* out_vals = static_cast<float*>(TF_TensorData(output_values[0]));
  for (int i = 0; i < 5; ++i)
  {
      std::cout << "Output values info: " << *out_vals++ << "\n";
  }

  fprintf(stdout, "Successfully run session\n");

//void* output_data = TF_TensorData(output_values[0]);
//assert(TF_GetCode(status) == TF_OK);
if (TF_GetCode(status) != TF_OK) {
          fprintf(stderr, "ERROR: Unable to run session %s", TF_Message(status));        
          return 1;
  } 
  TF_CloseSession( session, status );
  TF_DeleteSession( session, status );
  TF_DeleteSessionOptions( sess_opts );      
  TF_DeleteStatus(status);
  TF_DeleteImportGraphDefOptions(opts);
  TF_DeleteGraph(graph);                                                                  
  return 0;
  */
//---------------------------------------------------------------------------------------	
  /*
TF_Status* s = TF_NewStatus();
TF_Status * status = TF_NewStatus();
  
	
TF_Graph* graph = TF_NewGraph();
	
  TF_SessionOptions * options = TF_NewSessionOptions();
  TF_Session * session = TF_NewSession( graph, options, status );
  char hello[] = "Hello TensorFlow!";
  TF_Tensor * tensor = TF_AllocateTensor( TF_STRING, 0, 0, 8 + TF_StringEncodedSize( strlen( hello ) ) );
  TF_Tensor * tensorOutput;
  TF_OperationDescription * operationDescription = TF_NewOperation( graph, "Const", "hello" );
  TF_Operation * operation; 
  struct TF_Output output;

  TF_StringEncode( hello, strlen( hello ), 8 + ( char * ) TF_TensorData( tensor ), TF_StringEncodedSize( strlen( hello ) ), status );
  memset( TF_TensorData( tensor ), 0, 8 );
  TF_SetAttrTensor( operationDescription, "value", tensor, status );
  TF_SetAttrType( operationDescription, "dtype", TF_TensorType( tensor ) );
  operation = TF_FinishOperation( operationDescription, status );

  output.oper = operation;
  output.index = 0;

  TF_SessionRun( session, 0,
                 0, 0, 0,  // Inputs
                 &output, &tensorOutput, 1,  // Outputs
                 &operation, 1,  // Operations
                 0, status );

  printf( "status code: %i\n", TF_GetCode( status ) );
  printf( "%s\n", ( ( char * ) TF_TensorData( tensorOutput ) ) + 9 );

  TF_CloseSession( session, status );
  TF_DeleteSession( session, status );
  TF_DeleteStatus( status );
  TF_DeleteSessionOptions( options );  

  return 0;
  
}



/*
//------------------------------------------------------------------------------------------------------------------
TensorBuffer* 	TensorCApi::Buffer(const Tensor& tensor) 
		{ 
			return tensor.buf_; 
		}
Tensor 		TensorCApi::MakeTensor(TF_DataType type, const TensorShape& shape, TensorBuffer* buf) 
		{
			return Tensor(static_cast<DataType>(type), shape, buf);
		}
// Create an empty tensor of type 'dtype'. 'shape' can be arbitrary, but has to
 // result in a zero-sized tensor.
class TensorCApi {
public:
 static TensorBuffer* Buffer(const Tensor& tensor);
 static Tensor MakeTensor(TF_DataType type, const TensorShape& shape, TensorBuffer* buf);
}
// Put an image in the cameraImg mat
cv::resize(image->image, cameraImg, cv::Size(inputwidth, inputheight), 0, 0, cv::INTER_AREA);
// Create a new tensor pointing to that memory:
const int64_t tensorDims[4] = {1,inputheight,inputwidth,3};
int *imNumPt = new int(1);
TF_Tensor* tftensor = TF_NewTensor(TF_DataType::TF_UINT8, tensorDims, 4, cameraImg.data, inputheight * inputwidth * 3, NULL, imNumPt);
Tensor inputImg = tensorflow::TensorCApi::MakeTensor(tftensor->dtype, tftensor->shape, tftensor->buffer);
//------------------------------------------------------------------------------------------------------------------

#include <stdio.h>                                                                        
#include <stdlib.h>                                                                       
#include <tensorflow/c/c_api.h>                                                           


TF_Buffer* read_file(const char* file);                                                   

void free_buffer(void* data, size_t length) {                                             
        free(data);                                                                       
}                                              

// Graph definition from unzipped https://storage.googleapis.com/download.tensorflow.org/models/inception5h.zip
  // which is used in the Go, Java and Android examples                                   
  TF_Buffer* graph_def = read_file("tensorflow_inception_graph.pb");                      
  TF_Graph* graph = TF_NewGraph();
// Import graph_def into graph                                                          
  TF_Status* status = TF_NewStatus();                                                     
  TF_ImportGraphDefOptions* opts = TF_NewImportGraphDefOptions();                         
  TF_GraphImportGraphDef(graph, graph_def, opts, status);
  TF_DeleteImportGraphDefOptions(opts);
  if (TF_GetCode(status) != TF_OK) {
          fprintf(stderr, "ERROR: Unable to import graph %s", TF_Message(status));        
          return 1;
  }       
  fprintf(stdout, "Successfully imported graph");                                         
  TF_DeleteStatus(status);
  TF_DeleteBuffer(graph_def);                                                             

  // Use the graph                                                                        
  TF_DeleteGraph(graph);                                                                  
  return 0;



//------------------------------------------------------------------------------------------------------------------
const char* graph_def_data; // <-- your serialized GraphDef here
TF_Buffer graph_def = {graph_def_data, strlen(graph_def_data), nullptr};
// Import `graph_def` into `graph`
TF_ImportGraphDefOptions* import_opts = TF_NewImportGraphDefOptions();
TF_ImportGraphDefOptionsSetPrefix(import_opts, "import");
TF_GraphImportGraphDef(graph, &graph_def, import_opts, s);
assert(TF_GetCode(s) == TF_OK);

// Setup graph inputs
std::vector<TF_Output> inputs;
std::vector<TF_Tensor*> input_values;
// Add the placeholders you would like to feed, e.g.:
TF_Operation* placeholder = TF_GraphOperationByName(graph, "import/my_placeholder");
inputs.push_back({placeholder, 0});
TF_Tensor* tensor = TF_NewTensor(/*...*/
/*
input_values.push_back(tensor);

// Setup graph outputs
std::vector<TF_Output> outputs;
// Add the node outputs you would like to fetch, e.g.:
TF_Operation* output_op = TF_GraphOperationByName(graph, "import/my_output");
outputs.push_back({output_op, 0});
std::vector<TF_Tensor*> output_values(outputs.size(), nullptr);

// Run `graph`
TF_SessionOptions* sess_opts = TF_NewSessionOptions();
TF_Session* session = TF_NewSession(graph, sess_opts, s);
assert(TF_GetCode(s) == TF_OK);
TF_SessionRun(session, nullptr,
              &inputs[0], &input_values[0], inputs.size(),
              &outputs[0], &output_values[0], outputs.size(),
              nullptr, 0, nullptr, s);

void* output_data = TF_TensorData(output_values[0]);
assert(TF_GetCode(s) == TF_OK);

// If you have a more complicated workflow, I suggest making scoped wrapper
// classes that call these in their destructors
for (int i = 0; i < inputs.size(); ++i) TF_DeleteTensor(input_values[i]);
for (int i = 0; i < outputs.size(); ++i) TF_DeleteTensor(output_values[i]);
TF_CloseSession(session, s);
TF_DeleteSession(session, s);
TF_DeleteSessionOptions(sess_opts);
TF_DeleteImportGraphDefOptions(import_opts);
TF_DeleteGraph(graph);
TF_DeleteStatus(s);
*/


/*
// Reads a model graph definition from disk, and creates a session object you
// can use to run it.
Status LoadGraph(string graph_file_name, std::unique_ptr<tensorflow::Session>* session) {
	tensorflow::GraphDef graph_def;
	Status load_graph_status = ReadBinaryProto(tensorflow::Env::Default(), graph_file_name, &graph_def);
	if (!load_graph_status.ok()) {
		return tensorflow::errors::NotFound("Failed to load compute graph at '",graph_file_name, "'");
	}
	session->reset(tensorflow::NewSession(tensorflow::SessionOptions()));
	Status session_create_status = (*session)->Create(graph_def);
	if (!session_create_status.ok()) {
		return session_create_status;
	}
	return Status::OK();
}
// Analyzes the output of the Inception graph to retrieve the highest scores and
// their positions in the tensor, which correspond to categories.
Status GetTopLabels(const std::vector<Tensor>& outputs, int how_many_labels,Tensor* out_indices, Tensor* out_scores) {
	const Tensor& unsorted_scores_tensor = outputs[0];
	auto unsorted_scores_flat = unsorted_scores_tensor.flat<float>();
	std::vector<std::pair<int, float>> scores;
	for (int i = 0; i < unsorted_scores_flat.size(); ++i) {
		scores.push_back(std::pair<int, float>({i, unsorted_scores_flat(i)}));
	}
	std::sort(scores.begin(), scores.end(),[](const std::pair<int, float>& left,const std::pair<int, float>& right) {return left.second > right.second;});
	scores.resize(how_many_labels);
	Tensor sorted_indices(tensorflow::DT_INT32, {scores.size()});
	Tensor sorted_scores(tensorflow::DT_FLOAT, {scores.size()});
	for (int i = 0; i < scores.size(); ++i) {
		sorted_indices.flat<int>()(i) = scores[i].first;
		sorted_scores.flat<float>()(i) = scores[i].second;
	}
	*out_indices = sorted_indices;
	*out_scores = sorted_scores;
	return Status::OK();
}

// Takes a file name, and loads a list of labels from it, one per line, and
// returns a vector of the strings. It pads with empty strings so the length
// of the result is a multiple of 16, because our model expects that.
Status ReadLabelsFile(string file_name, std::vector<string>* result, size_t* found_label_count) {
	std::ifstream file(file_name);
	if (!file) {
		return tensorflow::errors::NotFound("Labels file ", file_name, " not found.");
	}
	result->clear();
	string line;
	while (std::getline(file, line)) {
		result->push_back(line);
	}
	*found_label_count = result->size();
	const int padding = 16;
	while (result->size() % padding) {
		result->emplace_back();
	}
	return Status::OK();
}

// Given the output of a model run, and the name of a file containing the labels
// this prints out the top five highest-scoring values.
Status PrintTopLabels(const std::vector<Tensor>& outputs,const std::vector<string>& labels, int label_count, float print_threshold) {
	const int how_many_labels = std::min(5, static_cast<int>(label_count));
	Tensor indices;
	Tensor scores;
	TF_RETURN_IF_ERROR(GetTopLabels(outputs, how_many_labels, &indices, &scores));
	tensorflow::TTypes<float>::Flat scores_flat = scores.flat<float>();
	tensorflow::TTypes<int32>::Flat indices_flat = indices.flat<int32>();
	for (int pos = 0; pos < how_many_labels; ++pos) {
		const int label_index = indices_flat(pos);
		const float score = scores_flat(pos);
		std::cout << labels[label_index] << " (" << label_index << "): " << score<<" \t";
		// Print the top label to stdout if it's above a threshold.
		if ((pos == 0) && (score > print_threshold)) {
			//std::cout << labels[label_index] << std::endl;
		}
	}
	std::cout << std::endl;
	return Status::OK();
}
*/

/* 	tensorflow
	  
	// creating a Tensor for storing the data
	tensorflow::Tensor input_tensor(tensorflow::DT_FLOAT, tensorflow::TensorShape({1,224,224,3}));
	auto input_tensor_mapped = input_tensor.tensor<float, 4>();
	 // First we load and initialize the model.
	string root_dir = "/home/linaro/label";
	string graph ="output_graph.pb";
	string labels_file_name ="output_labels.txt";
	string input_layer = "input";
	string output_layer = "final_result";
	int print_threshold = 50;
	std::unique_ptr<tensorflow::Session> session;
	string graph_path = tensorflow::io::JoinPath(root_dir, graph);
	Status load_graph_status = LoadGraph(graph_path, &session);
	if (!load_graph_status.ok()) {
		LOG(ERROR) << load_graph_status;
		return -1;
	}
	std::vector<string> labels;
	size_t label_count;
	Status read_labels_status = ReadLabelsFile(labels_file_name, &labels, &label_count);
	if (!read_labels_status.ok()) {
		LOG(ERROR) << read_labels_status;
	return -1;
	}
*/