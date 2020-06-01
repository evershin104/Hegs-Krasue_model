#include "calculates.h"
#include <QDebug>
calculates::calculates()
{

}

void calculates::takeN(int num)
{
    N = num; // Takes the number of agents to calculates class
}

void calculates::takeEps(double num)
{
    eps = num; // Takes conf. level to calculates class
}

void calculates::takeErr(double num)
{
    error = num; // Takes error to calculates class
}


int calculates::returnN()
{
    return N;
}

QVector<QVector<double>> calculates::returnOpinions()
{
    QVector<QVector<double>> opinions;
    for (int i = 0; i <= evolution.size() - 1; i++) {
        opinions.push_back({});
        for (int j = 0; j <= evolution[i].size() - 1; j++) {
            opinions[i].push_back(evolution[i][j].opinion);
        }
    }
    return opinions;
}

int calculates::returnCons()
{
    return consensus;
}

QVector<calculates::agent> calculates::init(int N)
{
    /** For drand48() **/
    QVector<agent> started = {};
    for (int i = 1 ; i <= N ; i++) {
        agent j;
        j.id = i;
        j.opinion = drand48();
        started.push_back(j);
    }
    return started;
}

QVector<calculates::agent> calculates::defineTG(QVector<calculates::agent> model)
{
    /** Clear containers with TGs **/
    for (int i = 0; i <= model.size() - 1; i++) {
        model[i].TG.clear();
    }
    for (int i = 0; i <= model.size() - 1; i++ ) {
        for (int j = 0; j <= model.size() - 1; j++ ) {
            if ((model[i].id != model[j].id) && (abs(model[i].opinion - model[j].opinion) <= eps))
            { model[i].TG.push_back(model[j].id); } //Define elements for TG for each agent
        }
    }
    return model;
}

QVector<calculates::agent> calculates::redefineOpinion(QVector<calculates::agent> model)
{
    QVector<agent> result = model;
    for (int i = 0; i <= model.size() - 1; i++) {
        double meanTG = 0;
        for (int j = 0; j <= model[i].TG.size() - 1; j++) {
            meanTG += model[model[i].TG[j] - 1].opinion;
        }
        if (meanTG != 0) { result[i].opinion = meanTG / model[i].TG.size(); }
    }
    return result;
}

bool calculates::checkOnConsensus(QVector<calculates::agent> model)
{
    systemClusters.clear();
    /** Key = power of TG, value = ID's vector of agents who has equal power of TG **/
    QMap<int, QVector<int>>  clusters;
    for (int i = 0; i <= model.size() - 1; i++) {
        for (int j = 0; j <= model.size() - 1; j++) {
            if ((model[i].TG.size() == model[j].TG.size()) && (abs(model[i].opinion - model[j].opinion)) <= error)  {
                if (!clusters[model[i].TG.size()].contains(model[i].id)) { clusters[model[i].TG.size()].push_back(model[i].id); }
            }
        }
    }
    systemClusters = clusters;
    int i =0;
    while ((abs(evolution[evolution.size() - 2][i].opinion - model[i].opinion) <= error) && (i != model.size() - 1)) { i++; }
    if (i == model.size() - 1) { return true; }
    else { return false; }
}


void calculates::initModel()
{
    QVector<agent> model = init(N);                                     // Makes vector of agents with drand48() opinions
    evolution.push_back(model);                                          // Adds model parsameters to evolution vector for time t = 0
    model = defineTG(model);                                              // Define TGs for each agent
    model = redefineOpinion(model);                                  // Redefine opinions for each agent
    evolution.push_back(model);                                         // Adds model parsameters to evolution vector for time t = 1
    int t = 1;
    while (!checkOnConsensus(model) && (t <= 500)) {
        t++;
        model = defineTG(model);
        model = redefineOpinion(model);
        evolution.push_back(model);
    }
    consensus = t;
}

QString calculates::DataToSet()
{
    QString toRet = "Clusters: " + QString::number(systemClusters.size()) + "\n" + (systemClusters.size() != 1 ? "Evolution stopped on T = " + QString::number(consensus) :  "Consensus on " + QString::number(consensus));
    return toRet;
}

void calculates::cleanEvol()
{
    evolution.clear();
}

