// spike_rate.cpp
double spike_rate(double scale, double t, int i) {
   std::cout<<"t = " << t << "s" <<std::endl;
   std::cout<<"spike count for neuron " << i << ": " <<brian::%%SPIKECOUNT%%[i]<<std::endl;
   return ta2d(t, i)*scale;
}

