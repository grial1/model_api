/// @file evaluation.h
/// @author Gastón Rial
/// @date 2019-06-16
/// @brief abstract class to be extended and implemented by InputDataset

#ifndef MODEL_API_INCLUDE_EVALUATION_H_
#define MODEL_API_INCLUDE_EVALUATION_H_

enum class MetricType { TP,         ///< True Positive
                        TN,         ///< True Negative
                        FP,         ///< False Positive
                        FN,         ///< False Negative
                        PRECISION,  ///< Precision
                        RECALL,     ///< Recall
                        FONE,       ///< F1-Score
                        ND          ///< Not defined
                    };

struct PerformaceMetric 
{
    
    PerformaceMetric(MetricType type):oType{type}{};
    PerformaceMetric(MetricType type, double m):oType{type},metric{m}{};
    MetricType getType() const { return this->oType;};

    double metric = 0;

    private:
        MetricType oType = MetricType::ND;

};

struct TruePositive : public  PerformaceMetric {

    TruePositive():PerformaceMetric{MetricType::TP}{};
    TruePositive(double metric):PerformaceMetric{MetricType::TP, metric}{};

}; 

struct TrueNegative : public  PerformaceMetric {

    TrueNegative():PerformaceMetric{MetricType::TN}{};
    TrueNegative(double metric):PerformaceMetric{MetricType::TN, metric}{};

};

struct FalseNegative : public  PerformaceMetric {

    FalseNegative():PerformaceMetric{MetricType::FN}{};
    FalseNegative(double metric):PerformaceMetric{MetricType::FN, metric}{};

};

struct FalsePostive : public  PerformaceMetric {

    FalsePostive():PerformaceMetric{MetricType::FP}{};
    FalsePostive(double metric):PerformaceMetric{MetricType::FP, metric}{};

};

struct Precision : public  PerformaceMetric {

    Precision():PerformaceMetric{MetricType::PRECISION}{};
    Precision(double metric):PerformaceMetric{MetricType::PRECISION, metric}{};

};

struct Recall : public  PerformaceMetric {

    Recall():PerformaceMetric{MetricType::RECALL}{};
    Recall(double metric):PerformaceMetric{MetricType::RECALL, metric}{};

};

struct F1Score : public  PerformaceMetric {

    F1Score():PerformaceMetric{MetricType::FONE}{};
    F1Score(double):PerformaceMetric{MetricType::FONE, metric}{};

};

#endif ///< MODEL_API_INCLUDE_EVALUATION_H_