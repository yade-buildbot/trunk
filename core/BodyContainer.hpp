// 2004 © Olivier Galizzi <olivier.galizzi@imag.fr>
// 2004 © Janek Kozicki <cosurgi@berlios.de>
// 2010 © Václav Šmilauer <eudoxos@arcig.cz>

#pragma once

#include<yade/lib/serialization/Serializable.hpp>

#include<boost/foreach.hpp>
#ifndef FOREACH
#  define FOREACH BOOST_FOREACH
#endif

#include<boost/tuple/tuple.hpp>

class Body;
class InteractionContainer;

#ifdef YADE_SUBDOMAINS
	#ifdef YADE_OPENMP
		#define YADE_PARALLEL_FOREACH_BODY_BEGIN(b,bodies) \
			const int _numSubdomains=bodies->numSubdomains(); \
			_Pragma("omp parallel for schedule(static,1)") \
			for(int _subDomain=0; _subDomain<_numSubdomains; _subDomain++) \
			FOREACH(b, bodies->getSubdomain(_subDomain)){
		#define YADE_PARALLEL_FOREACH_BODY_END() }
	#else
		#define YADE_PARALLEL_FOREACH_BODY_BEGIN(b,bodies) \
			assert(bodies->numSubdomains()==1); assert(bodies->getSubdomain(0).size()==bodies->size()); \
			FOREACH(b,*(bodies)){
		#define YADE_PARALLEL_FOREACH_BODY_END() }
	#endif
#else
	#if YADE_OPENMP
		#define YADE_PARALLEL_FOREACH_BODY_BEGIN(b_,bodies) const Body::id_t _sz(bodies->size()); _Pragma("omp parallel for") for(Body::id_t _id=0; _id<_sz; _id++){ if(unlikely(!(*bodies)[_id]))  continue; b_((*bodies)[_id]);
		#define YADE_PARALLEL_FOREACH_BODY_END() }
	#else
		#define YADE_PARALLEL_FOREACH_BODY_BEGIN(b,bodies) FOREACH(b,*(bodies)){
		#define YADE_PARALLEL_FOREACH_BODY_END() }
	#endif
#endif

/*
Container of bodies implemented as flat std::vector. It handles body removal and
intelligently reallocates free ids for newly added ones.
The nested iterators and the specialized FOREACH_BODY macros above will silently skip null body pointers which may exist after removal. The null pointers can still be accessed via the [] operator. 

Any alternative implementation should use the same API.
*/
class BodyContainer: public Serializable{
	private:
		typedef std::vector<shared_ptr<Body> > ContainerT;
		ContainerT body;
		Body::id_t lowestFree;
		Body::id_t findFreeId();
		#ifdef YADE_SUBDOMAINS
			Body::id_t findFreeDomainLocalId(int subDom);
			// subDomain data
			std::vector<std::vector<shared_ptr<Body> > > subDomains;
		#endif
	public:
		friend class InteractionContainer;  // accesses the body vector directly
		
		//An iterator that will automatically jump slots with null bodies
		class smart_iterator : public ContainerT::iterator {
			public:
			ContainerT::iterator end;
			smart_iterator& operator++() {
				ContainerT::iterator::operator++();
				while (!(this->operator*()) && end!=(*this)) ContainerT::iterator::operator++();
				return *this;}
			smart_iterator operator++(int) {smart_iterator temp(*this); operator++(); return temp;}
			smart_iterator& operator=(const ContainerT::iterator& rhs) {ContainerT::iterator::operator=(rhs); return *this;}
			smart_iterator& operator=(const smart_iterator& rhs) {ContainerT::iterator::operator=(rhs); end=rhs.end; return *this;}
			smart_iterator() {}
			smart_iterator(const ContainerT::iterator& source) {(*this)=source;}
			smart_iterator(const smart_iterator& source) {(*this)=source; end=source.end;}
		};

// 		typedef ContainerT::iterator iterator;
// 		typedef ContainerT::const_iterator const_iterator;
		typedef smart_iterator iterator;
		typedef const smart_iterator const_iterator;

		BodyContainer();
		virtual ~BodyContainer();
		Body::id_t insert(shared_ptr<Body>&);
		Body::id_t insert(shared_ptr<Body>& b, Body::id_t id);
	
		// mimick some STL api
		void clear();
		// by using simple vector<>::iterator's, we can hit null bodies 
// 		iterator begin() { return body.begin(); }
// 		iterator end() { return body.end(); }
// 		const_iterator begin() const { return body.begin(); }
// 		const_iterator end() const { return body.end(); }
// 		//with smart iterators
		iterator begin() {
			iterator temp(body.begin()); temp.end=body.end();
			return (body.begin()==body.end() || *temp)?temp:++temp;}
		iterator end() { iterator temp(body.end()); temp.end=body.end(); return temp;}
		const_iterator begin() const { return begin();}
		const_iterator end() const { return end();}

		size_t size() const { return body.size(); }
		shared_ptr<Body>& operator[](unsigned int id){ return body[id];}
		const shared_ptr<Body>& operator[](unsigned int id) const { return body[id]; }

		bool exists(Body::id_t id) const { return (id>=0) && ((size_t)id<body.size()) && ((bool)body[id]); }
		bool erase(Body::id_t id);
		

		#ifdef YADE_SUBDOMAINS
			/* subdomain support
				Only meaningful when using OpenMP, but we keep the interface for OpenMP-less build as well.
				Loop over all bodies can be achieved as shown below; this works for all possible scenarios:

				1. OpenMP-less build
				2. OpenMP build, but no sub-domains defined (the loop will be then sequential, over the global domain)
				3. OpenMP build, with sub-domains; each thread will handle one sub-domain
				
				#ifdef YADE_OPENMP
					#pragma omp parallel for schedule(static)
				#endif
				for(int subDom=0; subDom<scene->bodies->numSubdomains(); subDom++){
					FOREACH(const shared_ptr<Body>& b, scene->bodies->getSubdomain(subDom)){
						if(!b) continue;
					}
				}

				For convenience, this is all wrapped in YADE_PARALLEL_FOREACH_BODY macro, which then works like this:

				YADE_PARALLEL_FOREACH_BODY(const shared_ptr<Body>& b,scene->bodies){
					if(!b) continue

				}
			
			*/
			// initialized by the ctor, is omp_get_max_threads() for OpenMP builds and 1 for OpenMP-less builds
			const int maxSubdomains;
			private:
				// lowest free id for each sub-domain
				std::vector<Body::id_t> subDomainsLowestFree;
			public:
			// return subdomain with given number; if no subDomains are defined (which is always the case for OpenMP-less builds), return the whole domain
			const std::vector<shared_ptr<Body> >& getSubdomain(int subDom){ if(subDomains.empty()){ assert(subDom==0); return body; } assert((size_t)subDom<subDomains.size()); return subDomains[subDom]; }
			// return the number of actually defined subdomains; if no subdomains were defined, return 1, which has the meaning of the whole domain
			int numSubdomains(){ return std::max((size_t)1,subDomains.size()); }
			// convert global subId to subDomain number and domain-local id
			boost::tuple<int,Body::id_t> subDomId2domNumLocalId(Body::id_t subDomId) const { return boost::make_tuple(subDomId % maxSubdomains, subDomId / maxSubdomains); }
			// convert subDomain number and subDomain-local id to global subId
			Body::id_t domNumLocalId2subDomId(int domNum,Body::id_t localId) const { return localId*maxSubdomains+domNum; }

			// delete all subdomain data
			void clearSubdomains();
			// setup empty subdomains
			void setupSubdomains();
			// add body to a sub-domain; return false if there are no subdomains, true otherwise
			bool setBodySubdomain(const shared_ptr<Body>&, int subDom);
		#endif /* YADE_SUBDOMAINS */

		REGISTER_CLASS_AND_BASE(BodyContainer,Serializable);
		REGISTER_ATTRIBUTES(Serializable,(body));
		DECLARE_LOGGER;
};
REGISTER_SERIALIZABLE(BodyContainer);
