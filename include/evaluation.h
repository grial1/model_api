/// @file evaluation.h
/// @author Gastón Rial
/// @date 2019-06-16
/// @brief abstract class to be extended and implemented by InputDataset

#ifndef MODEL_API_INCLUDE_EVALUATION_H_
#define MODEL_API_INCLUDE_EVALUATION_H_

struct PerformaceMetric 
{
    
    double metric;

};

struct TruePositives : public  PerformaceMetric {}; 

struct TrueNegatives : public  PerformaceMetric {};

struct FalseNegatives : public  PerformaceMetric {};

struct FalsePostives : public  PerformaceMetric {};

struct Precision : public  PerformaceMetric {};

struct Recall : public  PerformaceMetric {};

struct F1Score : public  PerformaceMetric {};

#endif ///< MODEL_API_INCLUDE_EVALUATION_H_