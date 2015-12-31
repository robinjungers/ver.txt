#include "Column.hpp"

#include <vector>

using namespace glimac;
using namespace glm;

Column::Column(){
    buildVertices();
    initVertices();
}

void Column::buildVertices() {

	ShapeVertex vertex;

//face de devant

    vertex.position = vec3(-1.0, -1.0, 1.0);
    vertex.normal= vec3(0.0, 1.0, 0.0);
    vertex.texCoords = vec2(0.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0, 3.0, 1.0);
    vertex.normal= vec3(0.0, 1.0, 0.0);
    vertex.texCoords = vec2(0.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0, 3.0, 1.0);
    vertex.normal= vec3(0.0, 1.0, 0.0);
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0, 3.0, 1.0);
    vertex.normal= vec3(0.0, 1.0, 0.0); 
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);
            
    vertex.position = vec3(1.0, -1.0, 1.0);
    vertex.normal= vec3(0.0,1.0, 0.0); 
    vertex.texCoords = vec2(1.0, 1.0);

    m_vertices.push_back(vertex);
        
    vertex.position = vec3(-1.0, -1.0, 1.0);
    vertex.normal= vec3(0.0,1.0, 0.0); 
    vertex.texCoords = vec2(0.0, 1.0);

    m_vertices.push_back(vertex);

// face de dessous 

    vertex.position = vec3(-1.0, -1.0, -1.0);
    vertex.normal= vec3(0.0,1.0,0.0);
    vertex.texCoords = vec2(1.0, 0.0); 

    m_vertices.push_back(vertex); 

    vertex.position = vec3(-1.5, -1.0, 0.0);
    vertex.normal= vec3(0.0,1.0,0.0);   
    vertex.texCoords = vec2(0.0, 0.0); 

    m_vertices.push_back(vertex); 
   
    vertex.position = vec3(-1.0, -1.0, 1.0);
    vertex.normal= vec3(0.0,1.0,0.0);  
    vertex.texCoords = vec2(0.0, 1.0); 

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0, -1.0, 1.0);
    vertex.normal= vec3(0.0,1.0,0.0);  
    vertex.texCoords = vec2(0.0, 1.0); 

    m_vertices.push_back(vertex);   

    vertex.position = vec3(-1.0, -1.0, -1.0);
    vertex.normal= vec3(0.0,1.0,0.0);   
    vertex.texCoords = vec2(0.0, 0.0); 

    m_vertices.push_back(vertex);  

    vertex.position = vec3(1.0, -1.0, 1.0);
    vertex.normal= vec3(0.0,1.0,0.0);  
    vertex.texCoords = vec2(1.0, 1.0); 

    m_vertices.push_back(vertex);  

    vertex.position = vec3(1.0, -1.0, 1.0);
    vertex.normal= vec3(0.0,1.0,0.0);   
    vertex.texCoords = vec2(1.0, 1.0); 

    m_vertices.push_back(vertex);  

    vertex.position = vec3(1.0, -1.0, -1.0);
    vertex.normal= vec3(0.0,1.0,0.0);  
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);  

    vertex.position = vec3(-1.0, -1.0, -1.0);
    vertex.normal= vec3(0.0,1.0,0.0);   
    vertex.texCoords = vec2(0.0, 0.0); 

    m_vertices.push_back(vertex);  

    vertex.position = vec3(1.0, -1.0, -1.0);
    vertex.normal= vec3(0.0,1.0,0.0);  
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);  

    vertex.position = vec3(1.5, -1.0, 0.0);
    vertex.normal= vec3(0.0,1.0,0.0);   
    vertex.texCoords = vec2(0.0, 1.0); 

    m_vertices.push_back(vertex); 

    vertex.position = vec3(1.0, -1.0, 1.0);
    vertex.normal= vec3(0.0,1.0,0.0);   
    vertex.texCoords = vec2(1.0, 1.0); 

    m_vertices.push_back(vertex); 

// face de gauche - devant 

    vertex.position = vec3(-1.0, -1.0, 1.0);
    vertex.normal= vec3(0.0, 1.0, 0.0);   
    vertex.texCoords = vec2(1.0, 1.0); 

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.5, -1.0, 0.0);
    vertex.normal= vec3(0.0, 1.0, 0.0);  
    vertex.texCoords = vec2(0.0, 1.0); 

    m_vertices.push_back(vertex); 

    vertex.position = vec3(-1.0, 3.0, 1.0); 
    vertex.normal= vec3(0.0, 1.0, 0.0);  
    vertex.texCoords = vec2(1.0, 0.0); 

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0, 3.0, 1.0); 
    vertex.normal= vec3(0.0, 1.0, 0.0);  
    vertex.texCoords = vec2(1.0, 0.0); 

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.5, 3.0, 0.0); 
    vertex.normal= vec3(0.0, 1.0, 0.0);  
    vertex.texCoords = vec2(0.0, 0.0); 

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.5, -1.0, 0.0);
    vertex.normal= vec3(0.0, 1.0, 0.0);  
    vertex.texCoords = vec2(0.0, 1.0); 

    m_vertices.push_back(vertex); 

// face de gauche - derrière 

    vertex.position = vec3(-1.0, -1.0, -1.0);
    vertex.normal= vec3(0.0, 1.0, 0.0);   
    vertex.texCoords = vec2(1.0, 1.0); 

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.5, -1.0, 0.0);
    vertex.normal= vec3(0.0, 1.0, 0.0);  
    vertex.texCoords = vec2(0.0, 1.0); 

    m_vertices.push_back(vertex); 

    vertex.position = vec3(-1.5, 3.0, 0.0); 
    vertex.normal= vec3(0.0, 1.0, 0.0);  
    vertex.texCoords = vec2(0.0, 0.0); 

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.5, 3.0, 0.0); 
    vertex.normal= vec3(0.0, 1.0, 0.0);  
    vertex.texCoords = vec2(0.0, 0.0); 

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0, 3.0, -1.0); 
    vertex.normal= vec3(0.0, 1.0, 0.0);  
    vertex.texCoords = vec2(1.0, 0.0); 

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0, -1.0, -1.0);
    vertex.normal= vec3(0.0, 1.0, 0.0);  
    vertex.texCoords = vec2(1.0, 1.0); 

    m_vertices.push_back(vertex); 

// face de derrière  

    vertex.position = vec3(-1.0, -1.0, -1.0);
    vertex.normal= vec3(0.0,1.0, 0.0); 
    vertex.texCoords = vec2(0.0,1.0); 

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0, 3.0, -1.0 );
    vertex.normal = vec3( 0.0, 1.0, 0.0 );
    vertex.texCoords = vec2(0.0,0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0, 3.0, -1.0);
    vertex.normal = vec3( 0.0, 1.0, 0.0 );
    vertex.texCoords = vec2(1.0,0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0, 3.0, -1.0);
    vertex.normal = vec3(0.0,1.0, 0.0);
    vertex.texCoords = vec2(1.0,0.0);

    m_vertices.push_back(vertex);
 
    vertex.position = vec3(-1.0, -1.0,-1.0 );
    vertex.normal = vec3( 0.0, 1.0, 0.0 );
    vertex.texCoords = vec2(0.0,1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0, -1.0,-1.0 );
    vertex.normal = vec3( 0.0, 1.0, 0.0 );
    vertex.texCoords = vec2(1.0,1.0);

    m_vertices.push_back(vertex);

// face de droite - devant 

    vertex.position = vec3(1.0, -1.0, 1.0);
    vertex.normal = vec3(1.0, 1.0, 0.0 );
    vertex.texCoords = vec2( 0.0, 1.0 );

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0, 3.0, 1.0);
    vertex.normal = vec3(0.0, 1.0, 0.0 );
    vertex.texCoords = vec2( 0.0, 0.0 );

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.5, -1.0, 0.0);
    vertex.normal = vec3(0.0, 1.0, 0.0 );
    vertex.texCoords = vec2( 1.0, 1.0 );

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.5, -1.0, 0.0);
    vertex.normal = vec3(0.0, 1.0, 0.0 );
    vertex.texCoords = vec2( 1.0, 1.0 );

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.5, 3.0, 0.0);
    vertex.normal = vec3(0.0, 1.0, 0.0 );
    vertex.texCoords = vec2( 1.0, 0.0 );

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0, 3.0, 1.0);
    vertex.normal = vec3(0.0, 1.0, 0.0 );
    vertex.texCoords = vec2( 0.0, 0.0 );

    m_vertices.push_back(vertex);

// face de droite - derriere

    vertex.position = vec3(1.0, -1.0, -1.0);
    vertex.normal = vec3(0.0,1.0,0.0);
    vertex.texCoords = vec2(1.0,1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0, 3.0, -1.0);
    vertex.normal = vec3(0.0,1.0,0.0);
    vertex.texCoords = vec2(1.0,0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.5, 3.0, 0.0);
    vertex.normal = vec3(0.0, 1.0, 0.0);
    vertex.texCoords = vec2(0.0,0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.5, 3.0, 0.0);
    vertex.normal = vec3(0.0,1.0,0.0);
    vertex.texCoords = vec2(0.0,.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.5, -1.0, 0.0);
    vertex.normal = vec3(0.0,1.0,0.0);
    vertex.texCoords = vec2(0.0,1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0, -1.0, -1.0);
    vertex.normal = vec3(0.0,1.0,0.0);
    vertex.texCoords = vec2(1.0,1.0);

    m_vertices.push_back(vertex);

// face de dessus

    vertex.position = vec3(-1.0, 3.0, -1.0);
    vertex.normal = vec3(0.0,1.0,0.0);  
    vertex.texCoords = vec2(1.0, 0.0); 

    m_vertices.push_back(vertex); 

    vertex.position = vec3(-1.5, 3.0, 0.0);
    vertex.normal = vec3(0.0,1.0,0.0);  
    vertex.texCoords = vec2(0.0, 0.0); 

    m_vertices.push_back(vertex); 
   
    vertex.position = vec3(-1.0, 3.0, 1.0);
    vertex.normal = vec3(0.0,1.0,0.0);   
    vertex.texCoords = vec2(0.0, 1.0); 

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0, 3.0, 1.0);
    vertex.normal = vec3(0.0,1.0,0.0);    
    vertex.texCoords = vec2(0.0, 1.0); 

    m_vertices.push_back(vertex);   

    vertex.position = vec3(-1.0, 3.0, -1.0);
    vertex.normal = vec3(0.0,1.0,0.0);    
    vertex.texCoords = vec2(0.0, 0.0); 

    m_vertices.push_back(vertex);  

    vertex.position = vec3(1.0, 3.0, 1.0);
    vertex.normal = vec3(0.0,1.0,0.0);  
    vertex.texCoords = vec2(1.0, 1.0); 

    m_vertices.push_back(vertex);  

    vertex.position = vec3(1.0, 3.0, 1.0);
    vertex.normal = vec3(0.0,1.0,0.0);    
    vertex.texCoords = vec2(1.0, 1.0); 

    m_vertices.push_back(vertex);  

    vertex.position = vec3(1.0, 3.0, -1.0);
    vertex.normal = vec3(0.0,1.0,0.0); 
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);  

    vertex.position = vec3(-1.0, 3.0, -1.0);
    vertex.normal = vec3(0.0,1.0,0.0);     
    vertex.texCoords = vec2(0.0, 0.0); 

    m_vertices.push_back(vertex);  

    vertex.position = vec3(1.0, 3.0, -1.0);
    vertex.normal = vec3(0.0,1.0,0.0); 
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);  

    vertex.position = vec3(1.5, 3.0, 0.0);
    vertex.normal = vec3(0.0,1.0,0.0);   
    vertex.texCoords = vec2(0.0, 1.0); 

    m_vertices.push_back(vertex); 

    vertex.position = vec3(1.0, 3.0, 1.0);
    vertex.normal = vec3(0.0,1.0,0.0);   
    vertex.texCoords = vec2(1.0, 1.0); 

    m_vertices.push_back(vertex); 
}

void Column::animation() {

}