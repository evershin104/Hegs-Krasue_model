#ifndef CALCULATES_H
#define CALCULATES_H
#include <QVector>
#include <cmath>
#include <QMap>
#include <QString>
class calculates
{

    struct agent
    {
        int id;                                                                 // His order number
        double opinion;                                                 // From 0 to 1
        QVector<int> TG;                                               // Trust Group
    };

    int N; // Number of agents
    double eps, error;                                                   // Confidence level and error obviously
    QVector<QVector<agent>> evolution;                    // The evoluyion of opinions for each time
    int consensus;                                                        // Consensustime or time when the evolution stopped
    QMap<int, QVector<int>>  systemClusters;            // Clusters of system


public:
    calculates();

    void takeN(int num);                        //Takes number of agents
    void takeEps(double num);             // Takes confidence level
    void takeErr(double num);              // Takes error
    int returnN(void);                            // Returns N

    QVector<QVector<double>> returnOpinions(void);  //Returns opinions for time = t
    int returnCons(void);                                               // Returns t = consensus or t = 300 if there are no consensus before
    void initModel();                                                     // Main calculate function, it fills evolution vector
    QString DataToSet(void);                                        // Data to output, number of clusters and consensus time
    void cleanEvol(void);                                             // Clean evolution


private:
    QVector<agent> init(int N);                                                         // Inits the model when t = 0
    QVector<agent> defineTG(QVector<agent> model);                   // Defines trust groups for each agent
    QVector<agent> redefineOpinion(QVector<agent> model);       // Defines opinion for each agent
    bool checkOnConsensus (QVector<agent> model);                   // Checks the model for consensus conditions
                                                                                                      // and counts clusters of agents

};

#endif // CALCULATES_H
