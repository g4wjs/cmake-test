set (SCM_VERSION Unknown)

if (EXISTS "${SOURCE_DIR}/.svn")
  # the FindSubversion.cmake module is part of the standard distribution
  include (FindSubversion)

  if (Subversion_FOUND)
    # extract working copy information for SOURCE_DIR into MY_XXX variables
    Subversion_WC_INFO (${SOURCE_DIR} MY)
    set (SCM_VERSION ${MY_WC_REVISION})
  else (Subversion_FOUND)
    message (WARNING "Subversion not found, cannot determine SCM version")
  endif (Subversion_FOUND)
elseif (EXISTS "${SOURCE_DIR}/.git")
  find_package (Git)
  if (GIT_FOUND)
    execute_process (
      COMMAND ${GIT_EXECUTABLE} describe --always --dirty
      WORKING_DIRECTORY ${SOURCE_DIR}
      RESULT_VARIABLE git-exit-code
      OUTPUT_VARIABLE git-output
      ERROR_VARIABLE git-error
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_STRIP_TRAILING_WHITESPACE
      )
    if (${git-exit-code})
      message (WARNING "Git failed - ${git-error}")
    else (${git-exit-code})
      set (SCM_VERSION ${git-output})
    endif (${git-exit-code})
  else (GIT_FOUND)
    message (WARNING "Git package not found, cannot determine SCM version.")
  endif (GIT_FOUND)
endif ()

# write a file with the SCM_VERSION define
file (WRITE scm_version.h.txt "#define SCM_VERSION ${SCM_VERSION}\n")

# copy the file to the final header only if the version changes
# reduces needless rebuilds
execute_process (COMMAND ${CMAKE_COMMAND} -E copy_if_different scm_version.h.txt scm_version.h)
