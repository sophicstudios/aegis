project(agt)

################################################################################
# agta group
################################################################################

set(AGTA_SOURCES
    agta/agta_assetpool.cpp
    agta/agta_assetpool.h
    agta/agta_material.cpp
    agta/agta_material.h
    agta/agta_mesh.cpp
    agta/agta_mesh.h
)

set(AGTA_SOURCES_TEST
    agta/agta_assetpool.t.cpp
)

source_group(agta FILES ${AGTA_SOURCES} ${AGTA_SOURCES_TEST})

################################################################################
# agtc group
################################################################################

set(AGTC_SOURCES
    agtc/agtc_componenthandle.cpp
    agtc/agtc_componenthandle.h
    agtc/agtc_spriteanimationcomponent.cpp
    agtc/agtc_spriteanimationcomponent.h
    agtc/agtc_transformcomponent.cpp
    agtc/agtc_transformcomponent.h
    agtc/agtc_visual2dcomponent.cpp
    agtc/agtc_visual2dcomponent.h
)

set(AGTC_SOURCES_TEST
)

source_group(agtc FILES ${AGTC_SOURCES} ${AGTC_SOURCES_TEST})

################################################################################
# agte group
################################################################################

set(AGTE_SOURCES
    agte/agte_camera.cpp
    agte/agte_camera.h
    agte/agte_pool.cpp
    agte/agte_pool.h
    agte/agte_engine.cpp
    agte/agte_engine.h
    agte/agte_entity.cpp
    agte/agte_entity.h
    agte/agte_eventsystem.cpp
    agte/agte_eventsystem.h
    agte/agte_orthographiccamera.cpp
    agte/agte_orthographiccamera.h
    agte/agte_platform.cpp
    agte/agte_platform.h
    agte/agte_rendersystem.cpp
    agte/agte_rendersystem.h
    agte/agte_space.cpp
    agte/agte_space.h
    agte/agte_spritesystem.cpp
    agte/agte_spritesystem.h
    agte/agte_surface.cpp
    agte/agte_surface.h
    agte/agte_system.cpp
    agte/agte_system.h
)

set(AGTE_SOURCES_TEST
    agte/agte_pool.t.cpp
)

source_group(agte FILES ${AGTE_SOURCES} ${AGTE_SOURCES_TEST})

################################################################################
# agtg group
################################################################################

set(AGTG_SOURCES
    agtg/agtg_colorrgba.cpp
    agtg/agtg_colorrgba.h
    #agtg/agtg_colorutil.cpp
    #agtg/agtg_colorutil.h
    agtg/agtg_gl.cpp
    agtg/agtg_gl.h
    agtg/agtg_model.cpp
    agtg/agtg_model.h
    agtg/agtg_renderingcontext.cpp
    agtg/agtg_renderingcontext.h
    agtg/agtg_shaderprogram.cpp
    agtg/agtg_shaderprogram.h
    agtg/agtg_texture.cpp
    agtg/agtg_texture.h
    agtg/agtg_vertex.cpp
    agtg/agtg_vertex.h
)

set(AGTG_SOURCES_TEST
    agtg/agtg_colorrgba.t.cpp
)

source_group(agtg FILES ${AGTG_SOURCES} ${AGTG_SOURCES_TEST})

################################################################################
# agtm group
################################################################################

set(AGTM_SOURCES
    agtm/agtm_matrix2.cpp
    agtm/agtm_matrix2.h
    agtm/agtm_matrix2util.cpp
    agtm/agtm_matrix2util.h
    agtm/agtm_matrix3.cpp
    agtm/agtm_matrix3.h
    agtm/agtm_matrix3util.cpp
    agtm/agtm_matrix3util.h
    agtm/agtm_matrix4.cpp
    agtm/agtm_matrix4.h
    agtm/agtm_matrix4util.cpp
    agtm/agtm_matrix4util.h
    agtm/agtm_quaternion.cpp
    agtm/agtm_quaternion.h
    agtm/agtm_rect.cpp
    agtm/agtm_rect.h
    agtm/agtm_size2d.cpp
    agtm/agtm_size2d.h
    agtm/agtm_vector2.cpp
    agtm/agtm_vector2.h
    agtm/agtm_vector2util.cpp
    agtm/agtm_vector2util.h
    agtm/agtm_vector3.cpp
    agtm/agtm_vector3.h
    agtm/agtm_vector3util.cpp
    agtm/agtm_vector3util.h
    agtm/agtm_vector4.cpp
    agtm/agtm_vector4.h
)

set(AGTM_SOURCES_TEST
    agtm/agtm_matrix2.t.cpp
    agtm/agtm_matrix2util.t.cpp
    agtm/agtm_matrix3.t.cpp
    agtm/agtm_matrix3util.t.cpp
    agtm/agtm_matrix4.t.cpp
    agtm/agtm_matrix4util.t.cpp
    agtm/agtm_quaternion.t.cpp
    agtm/agtm_vector2.t.cpp
    agtm/agtm_vector2util.t.cpp
    agtm/agtm_vector3.t.cpp
    agtm/agtm_vector3util.t.cpp
    agtm/agtm_vector4.t.cpp
)

source_group(agtm FILES ${AGTM_SOURCES} ${AGTM_SOURCES_TEST})

################################################################################
# agtr group
################################################################################

set(AGTR_SOURCES
    agtr/agtr_image.cpp
    agtr/agtr_image.h
    agtr/agtr_imageloaderpng.cpp
    agtr/agtr_imageloaderpng.h
    agtr/agtr_resource.cpp
    agtr/agtr_resource.h
)

set(AGTR_SOURCES_TEST
)

source_group(agtr FILES ${AGTR_SOURCES} ${AGTR_SOURCES_TEST})

################################################################################
# agtu group
################################################################################

set(AGTU_SOURCES
    agtu/agtu_modelimporter.h
)

set(AGTU_SOURCES_TEST
)

source_group(agtu FILES ${AGTU_SOURCES} ${AGTU_SOURCES_TEST})

################################################################################
# agtui group
################################################################################

set(AGTUI_SOURCES
    agtui/agtui_boxsizer.cpp
    agtui/agtui_boxsizer.h
    agtui/agtui_displaytimer.cpp
    agtui/agtui_displaytimer.h
    agtui/agtui_glview.cpp
    agtui/agtui_glview.h
    agtui/agtui_mouseevent.cpp
    agtui/agtui_mouseevent.h
    agtui/agtui_sizer.cpp
    agtui/agtui_sizer.h
    agtui/agtui_touchevent.cpp
    agtui/agtui_touchevent.h
    agtui/agtui_widget.cpp
    agtui/agtui_widget.h
)

set(AGTUI_SOURCES_TEST
)

source_group(agtui FILES ${AGTUI_SOURCES} ${AGTUI_SOURCES_TEST})

################################################################################
# agt library
################################################################################

set(${PROJECT_NAME}_SOURCES_LOCAL
    ${AGTA_SOURCES}
    ${AGTC_SOURCES}
    ${AGTE_SOURCES}
    ${AGTG_SOURCES}
    ${AGTM_SOURCES}
    ${AGTR_SOURCES}
    ${AGTU_SOURCES}
    ${AGTUI_SOURCES}
)

set(${PROJECT_NAME}_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/agta
    ${PROJECT_SOURCE_DIR}/agtc
    ${PROJECT_SOURCE_DIR}/agte
    ${PROJECT_SOURCE_DIR}/agtg
    ${PROJECT_SOURCE_DIR}/agtm
    ${PROJECT_SOURCE_DIR}/agtr
    ${PROJECT_SOURCE_DIR}/agtu
    ${PROJECT_SOURCE_DIR}/agtui
    CACHE INTERNAL "${PROJECT_NAME}: Include dirs" FORCE)

include_directories(
    ${${PROJECT_NAME}_INCLUDE_DIRS}
    ${aft_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
)

add_library(${PROJECT_NAME} OBJECT ${${PROJECT_NAME}_SOURCES_LOCAL})
target_link_libraries(${PROJECT_NAME} PUBLIC aft ${PNG_LIBRARIES} ${OPENGL_LIBRARIES})

target_compile_options(${PROJECT_NAME} PRIVATE "-Wall")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS_GLOB ${${PROJECT_NAME}_INCLUDE_DIRS} "*.h")
set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS_GLOB} PARENT_SCOPE)
set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES_LOCAL} PARENT_SCOPE)

################################################################################
# agt unit tests
################################################################################

set(AGT_SOURCES_TEST
    ${AGTA_SOURCES_TEST}
    ${AGTC_SOURCES_TEST}
    ${AGTE_SOURCES_TEST}
    ${AGTG_SOURCES_TEST}
    ${AGTM_SOURCES_TEST}
    ${AGTR_SOURCES_TEST}
    ${AGTU_SOURCES_TEST}
    ${AGTUI_SOURCES_TEST}
    agt.t.cpp
)

source_group(driver FILES agt.t.cpp)

include_directories(${${PROJECT_NAME}_INCLUDE_DIRS}
    ${aft_INCLUDE_DIRS}
    ${aunit_INCLUDE_DIRS}
)

add_executable(test_${PROJECT_NAME} ${AGT_SOURCES_TEST})
target_link_libraries(test_${PROJECT_NAME} ${PROJECT_NAME} aft aunit)

target_compile_options(test_${PROJECT_NAME} PRIVATE "-Wall")
set_property(TARGET test_${PROJECT_NAME} PROPERTY CXX_STANDARD 14)


