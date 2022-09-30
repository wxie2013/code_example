// spike_rate.cpp
#define get_name(var) #var
double spike_rate(double scale, double t, int i) {
   std::cout<<"t = " << t << "s" <<std::endl;
   std::cout<<get_name(brian::_array_syn_count)<<" spike count for neuron " << i << ": " <<brian::_array_syn_count[i]<<std::endl;
   std::cout<<"scale: "<<scale<<std::endl;
   return ta2d(t, i)*scale;
}
